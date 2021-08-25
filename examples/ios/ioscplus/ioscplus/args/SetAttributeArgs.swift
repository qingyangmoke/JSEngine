//
//  SetAttributeArgs.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation

public struct SetAttributeArgs: Decodable {
    let uniqueId: Int32
    let attribute: [String:String]
}
