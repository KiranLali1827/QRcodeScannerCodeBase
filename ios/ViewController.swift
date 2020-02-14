//
//  AppDelegate.swift
//  qrcodescanner
//
//  Created by Pri Tam on 2/14/20.
//  Copyright © 2020 Veridium IP Ltd. All rights reserved.
//

import UIKit
import VeridiumCore
import Veridium4FExportBiometrics
import VeridiumIndividualFingerSelector


class ViewController: UIViewController,UIPickerViewDataSource,UIPickerViewDelegate, ViewControllerIndividualDelegate {
    
    @IBOutlet weak var captureButton: UIButton!
    @IBOutlet weak var capture8FButton: UIButton!
    @IBOutlet weak var captureIndexButton: UIButton!
    @IBOutlet weak var capture2IndexButton: UIButton!
    @IBOutlet weak var capture2ThumbButton: UIButton!
    @IBOutlet weak var captureAllFingerButton: UIButton!
    @IBOutlet weak var selectIndividualFButton: UIButton!
    @IBOutlet weak var IndividualFExportButton: UIButton!
    
    @IBOutlet weak var saveDirectoryLabel: UILabel!
    @IBOutlet weak var lastCaptureFilenameLabel: UILabel!
    @IBOutlet weak var versionLabel: UILabel!
    
    @IBOutlet weak var formatSelectorSpinner : UIPickerView!
    
    @IBOutlet weak var livenessSwitch: UISwitch!
    
    
    var saveFileDirectory :  URL!
    
    var exportConfig : VeridiumBiometrics4FConfig = VeridiumBiometrics4FConfig()
    var exportFormat : VeridiumTemplateFormat = FORMAT_JSON;
    
    var is4FSupportedByFormat = true
    var is8FSupportedByFormat = true
    var is2ThumbSupportedByFormat = true
    var isAllFingerCaptureSupportedByFormat = true
    var thumbMode = ThumbNone
    var isFingersSelectedComplete = false
    
    var saveCount : Int = 0
    var formatTypeData : Array<String> = ["Veridium FP", "Nist", "Interpol", "Zip (+8F)", "JSON (+8F)", "ISO-4 2005 (+8F)", "ISO-2 2005"]
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.captureButton.isExclusiveTouch = true
        self.captureIndexButton.isExclusiveTouch = true
        self.capture8FButton.isExclusiveTouch = true
        self.capture2IndexButton.isExclusiveTouch = true
        self.capture2ThumbButton.isExclusiveTouch = true
        self.captureAllFingerButton.isExclusiveTouch = true
        self.selectIndividualFButton.isExclusiveTouch = true
        self.IndividualFExportButton.isExclusiveTouch = true
        
        //self.IndividualFExportButton.isEnabled = isFingersSelectedComplete //done in UI update?
        
        self.setVersionlabel();
        self.setupSaveDirectory();
        self.setupFormatSpinner();
        self.updateUI();
    }
    
    func updateUI() {
        self.captureButton.isEnabled = is4FSupportedByFormat
        self.captureIndexButton.isEnabled = is4FSupportedByFormat
        self.capture8FButton.isEnabled = is8FSupportedByFormat
        self.capture2IndexButton.isEnabled = is8FSupportedByFormat
        self.capture2ThumbButton.isEnabled = is2ThumbSupportedByFormat
        self.captureAllFingerButton.isEnabled = isAllFingerCaptureSupportedByFormat
        self.IndividualFExportButton.isEnabled = isFingersSelectedComplete && is2ThumbSupportedByFormat
    }
    
    func setVersionlabel() {
        let version = Bundle.main.infoDictionary?["CFBundleShortVersionString"] ?? ""
        let build = Bundle.main.infoDictionary?[kCFBundleVersionKey as String] ?? ""
        let strVer = "v\(version)(\(build))"
        self.versionLabel.text = strVer;
    }
    
    func setupSaveDirectory() {
        saveFileDirectory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        saveFileDirectory = saveFileDirectory.appendingPathComponent("Veridium").appendingPathComponent("ExportDemo")
        do {
            try FileManager.default.createDirectory(atPath: saveFileDirectory.path, withIntermediateDirectories: true, attributes: nil)
        } catch let error as NSError {
            print(error.localizedDescription);
        }
        saveCount = 0;
    }
    
    // Generate a file path and save the vector to disk
    func writeVectorToDisk(_ biometricVector:VeridiumBiometricFullVector, _ fileExtension:String) {
        let basefilename = "swift_fingerprints_" + String(self.saveCount) + "_";
        let dateFormatter = DateFormatter();
        dateFormatter.dateFormat = "YYYY.MM.dd_HH.mm.ss";
        let currentDate = Date();
        let dateString = dateFormatter.string(from: currentDate);
        let fullFileName = basefilename.appending(dateString).appending(fileExtension);
        let fullFilePath = self.saveFileDirectory.appendingPathComponent(fullFileName);
        print("Saving file.");
        print(fullFilePath);
        
        do {
            try biometricVector.biometricData.write(to: fullFilePath);
            self.lastCaptureFilenameLabel.text = "Last capture filename : " + fullFileName;
            self.saveCount += 1;
        } catch let error as NSError {
            print(error.localizedDescription);
        }
    }
    
    func setupFormatSpinner() {
        formatSelectorSpinner.dataSource = self
        formatSelectorSpinner.delegate = self
        
        formatSelectorSpinner.selectRow(3, inComponent: 0, animated: false) // Default to Zip
        pickerView(formatSelectorSpinner, didSelectRow: 3, inComponent: 0)
    }
    
    @IBAction func onPrivacyPolicy(_ sender: AnyObject){
        let currentStoryboard = self.storyboard!;
        let infoVc = currentStoryboard.instantiateViewController(withIdentifier: "policyDialog")
        infoVc.modalPresentationStyle = .overCurrentContext
        infoVc.presentInTopmost();
    }
    
    @IBAction func onExport(_ sender: AnyObject) {
        exportConfig.chosenHand = Veridium4FExHandChoiceEitherHandEnroll;
        exportConfig.individualCapture = false;
        thumbMode = ThumbNone;
        commonExport(false, target_index: false, target_little: false)
    }
    
    @IBAction func onExport8F(_ sender: AnyObject) {
        exportConfig.chosenHand = Veridium4FExHandChoiceEitherHandEnroll;
        exportConfig.individualCapture = false;
        thumbMode = ThumbNone;
        commonExport(true, target_index: false, target_little: false)
    }
    
    @IBAction func onExportIndex(_ sender: Any) {
        exportConfig.chosenHand = Veridium4FExHandChoiceEitherHandEnroll;
        exportConfig.individualCapture = false;
        thumbMode = ThumbNone;
        commonExport(false, target_index: true, target_little: false)
    }
    
    @IBAction func onExport2Index(_ sender: Any) {
        exportConfig.chosenHand = Veridium4FExHandChoiceEitherHandEnroll;
        exportConfig.individualCapture = false;
        thumbMode = ThumbNone;
        commonExport(true, target_index: true, target_little: false)
    }
    
    @IBAction func onExportAllFinger(_ sender: Any) {
        exportConfig.chosenHand = Veridium4FExHandChoiceEitherHandEnroll;
        exportConfig.individualCapture = false;
        thumbMode = ThumbNone;
        commonExport(true, target_index: true, target_little: true)
    }
    
    @IBAction func onTwoThumb(_ sender: Any) {
        thumbMode = Thumb2F;
        exportConfig.chosenHand = Veridium4FExHandChoiceEitherHandEnroll;
        exportConfig.individualCapture = false;
        commonExport(true, target_index: false, target_little: false)
    }
    
    @IBAction func onIndividualFPressed(_ sender: Any){
        let bundle = Bundle.init(identifier: "com.veridiumid.VeridiumIndividualFingerSelector");
        let storyboard = UIStoryboard.init(name: "Main", bundle: bundle);
        var IndividualFVC = ViewControllerIndividual();
        IndividualFVC = storyboard.instantiateViewController(withIdentifier: "IndividualFingerScreen") as! ViewControllerIndividual;
        IndividualFVC.modalPresentationStyle = .overCurrentContext;
        IndividualFVC.exportConfig = exportConfig;
        IndividualFVC.delegate = self;
        IndividualFVC.presentInTopmost();
    }
    
    @IBAction func onIndividualFExport(_ sender: Any){
        exportConfig.individualCapture = true;
        thumbMode = ThumbNone;
        commonExport(false, target_index:false, target_little:false)
    }
    
    
    func getItemsFromViewControllerAndStart(_ controller: ViewControllerIndividual!, withExport config: VeridiumBiometrics4FConfig!) {
        isFingersSelectedComplete = config.individualCapture;
        exportConfig.individualThumb = config.individualThumb;
        exportConfig.individualIndex = config.individualIndex;
        exportConfig.individualMiddle = config.individualMiddle;
        exportConfig.individualRing = config.individualRing;
        exportConfig.individualLittle = config.individualLittle;
        exportConfig.individualCapture = config.individualCapture;
        exportConfig.chosenHand = config.chosenHand;
        updateUI();
    }
    
    func commonExport(_ record8F: Bool, target_index: Bool, target_little: Bool) {
        exportConfig.record8F = record8F
        exportConfig.exportFormat = exportFormat
        exportConfig.targetIndexFinger = target_index;
        exportConfig.targetLittleFinger = target_index && target_little;
        exportConfig.wsq_compression_ratio = COMPRESS_10to1;
        exportConfig.pack_debug_data = false
        exportConfig.calculate_nfiq = false
        exportConfig.extra_scaled_image = true
        exportConfig.fixed_print_width = 0;
        exportConfig.fixed_print_height = 0;
        exportConfig.pack_audit_image = true
        exportConfig.reliability_mask = false
        exportConfig.background_remove = true
        exportConfig.pack_raw = true
        exportConfig.pack_png = true
        exportConfig.useLiveness = livenessSwitch.isOn
        // exportConfig.padding_width = 500   // Does not occure when exporting
        // exportConfig.padding_height = 500
        exportConfig.captureThumb = thumbMode
        
        VeridiumBiometrics4FExService.exportTemplate(exportConfig, onSuccess: { (biometricVector) in
            self.writeVectorToDisk(biometricVector, self.exportConfig.formatExtension());
            VeridiumUtils.alert("Export success", title:"Success");
        }, onFail: {
            print("Export failed.")
        }, onCancel: {
            print("Export cancelled");
        }, onError: {
            (error) in
            VeridiumUtils.alert(error.localizedDescription, title: "Error");
        });
    }
    
    
    // Controls the spinner/picker for choosing the format.
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1;
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return formatTypeData.count;
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return formatTypeData[row];
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        switch row {
        case 0:
            exportFormat = FORMAT_VERID
        case 1:
            exportFormat = FORMAT_NIST
        case 2:
            exportFormat = FORMAT_INTERPOL
        case 3:
            exportFormat = FORMAT_ZIP
        case 4:
            exportFormat = FORMAT_JSON
        case 5:
            exportFormat = FORMAT_ISO2005_4
        case 6:
            exportFormat = FORMAT_ISO2005_2
        default:
            exportFormat = FORMAT_JSON // Impossible
        }
        exportConfig.exportFormat = exportFormat;
        is4FSupportedByFormat = exportConfig.supports4F();
        is8FSupportedByFormat = exportConfig.supports8F();
        is2ThumbSupportedByFormat = exportConfig.supports2Thumb();
        isAllFingerCaptureSupportedByFormat = exportConfig.supportsAllFinger();
        updateUI();
    }
    
}


