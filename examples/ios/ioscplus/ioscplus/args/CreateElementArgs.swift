//
//  CreateElementArgs.swift
//  ioscplus
//
//  Created by song on 2021/8/24.
//

import Foundation


public struct CreateElementArgs: Decodable {
    let uniqueId: Int32;
    let tagName: String?;
}
