//
//  SetStyleArgs.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation

public struct SetStyleArgs: Decodable {
    let uniqueId: Int32
    let replace: Int32?
    let style: [String:String]
}
