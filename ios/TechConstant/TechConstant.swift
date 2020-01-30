//
//  TechConstant.swift
//  qrcodescanner
//
//  Created by Pri Tam on 1/30/20.
//  Copyright © 2020 Facebook. All rights reserved.
//

import Foundation


struct NetworkContants
{
    static let license = "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"
}