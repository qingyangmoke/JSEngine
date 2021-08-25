//
//  ReplaceChildArgs.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation

public struct ReplaceChildArgs: Decodable {
    let uniqueId: Int32
    let newChild: ChildArgs
    let oldChild: ChildArgs
}
