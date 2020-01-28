//
//  BiometricsEnrollmentProtocol.swift
//  VeridiumAuthenticator
//
//  Created by Catalin Stoica on 18/01/2018.
//  Copyright © 2018 VeridiumIP. All rights reserved.
//

import VeridiumBOPS
import VeridiumVFaceBiometrics
import Veridium4FBiometrics

protocol FourFEnrollmentPresenterProtocol{
  func onEnroll(hand: EnrollHand)
  func onCancelEnrollment()
}

class FourFEnrollmentPresenter: FourFEnrollmentPresenterProtocol {

  var arrayOfEnrollers : [VeridiumBioEnroller] = []
  var enrolmentResult: BiometricsEnrollmentProtocol?

  func onCancelEnrollment() {
    VIDRevocationService.shared().wipeAccount {
        self.enrolmentResult?.onEnrollmentCancelled()
    }
  }
    
    func onFailEnrollment(reason: String) {
        VIDRevocationService.shared().wipeAccount {
            self.enrolmentResult?.onBiometricEnrollmentFailed(reason: reason)
        }
    }
    
    func onEnroll(hand: EnrollHand) {
        VeridiumSDK.shared.enroller4F?.config.enrollHand = hand.getHandConfig()
        VeridiumSDK.shared.enroller4F?.enroll({ (vector) in
            if let account = VIDSetupService().defaultAccountService?.activeAccount {

                let theIntegration = integrationForOngoingBopsRegistration ?? VIDSetupService.firstPairing()?.integration
                if let authenticatorType = theIntegration?.authenticatorType {

                    account.changeBiometrics([vector], authenticatorType: authenticatorType, withCompletion: { (error) in
                        if let error = error {
                            print(error)
                            self.onFailEnrollment(reason: error.localizedDescription)
                            return
                        }

                        let handConfig = VeridiumSDK.shared.enroller4F?.config.enrollHand
                        let hand = handConfig?.getEnrollHand() ?? EnrollHand.either
                        account.enrolledHand = hand.description
                        account.profiles[0].authenticationHand = AuthHand(enrolledHand: hand)

                        self.enrolmentResult?.onBiometricEnrollmentSucceeded()
                    })
                } else {
                    self.onFailEnrollment(reason: "Biometric Enrollment Failed. Integration not found.")
                }
            }
            else {
                self.onFailEnrollment(reason: "Biometric Enrollment Failed. Account not found.")
            }
        }, onFail: {
            self.onFailEnrollment(reason: "Biometric Enrollment Failed")
        }, onCancel: {
            self.onCancelEnrollment()
        }, onError: { (error) in
            if error.toNSError.code == -5 { //-5 aka Veridium4FFatalError
                self.onFailEnrollment(reason: "Incompatible device. Application only supported on iOS devices with LED flash.")
            } else {
                self.onFailEnrollment(reason: error.localizedDescription)
            }
        })
    }
}

fileprivate extension Veridium4FHandChoiceEnroll {
    func getEnrollHand() -> EnrollHand {
        switch self {
            case .forceLeftHandEnroll:
                return .left
            case .forceRightHandEnroll:
                return .right
            case .bothHands:
                return .both
            case .eitherHandEnroll:
                return .either
        }
    }
}

fileprivate extension EnrollHand {
    func getHandConfig() -> Veridium4FHandChoiceEnroll {
        switch self {
            case .left:
                return .forceLeftHandEnroll
            case .right:
                return .forceRightHandEnroll
            case .both:
                return .bothHands
            case .either:
                return .eitherHandEnroll
        }
    }
}
