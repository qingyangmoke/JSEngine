//
//  JSTimerModule.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation

struct SetIntervalArgs: Decodable {
    let id: Int32;
    let interval: Int32;
}

struct SetTimeoutArgs: Decodable {
    let id: Int32;
    let delay: Int32;
}

struct ClearArgs: Decodable {
    let id: Int32;
}

public class JSTimerModule : NativeModule {
    private var _timers: [Int32:JSTimer] = [:];
    public init(scope: JSEngineScope) {
        super.init(moduleName: "JSMTimer", scope: scope);
    }
    
    public override func invokeMethod(callId: Int32, methodName: String, args: String) -> String {
        switch methodName {
        case "setInterval":
            if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
                if let setIntervalArgs = try? JSONDecoder().decode(SetIntervalArgs.self, from: data) {
                    let timer = JSTimer(id: setIntervalArgs.id, scope: getScope());
                    timer.setInterval(interval: setIntervalArgs.interval);
                    _timers.updateValue(timer, forKey: setIntervalArgs.id);
                    NSLog("setInterval=%d", setIntervalArgs.id);
                    return String(setIntervalArgs.id);
                }
            }
            return "-1";
            break;
        case "setTimeout":
            if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
                if let setTimeoutArgs = try? JSONDecoder().decode(SetTimeoutArgs.self, from: data) {
                    let timer = JSTimer(id: setTimeoutArgs.id, scope: getScope());
                    timer.setTimeout(delay: setTimeoutArgs.delay);
                    _timers.updateValue(timer, forKey: setTimeoutArgs.id);
                    NSLog("setTimeout=%d", setTimeoutArgs.id);
                    return String(setTimeoutArgs.id);
                }
            }
            return "-1";
            break;
        case "clearTimeout":
            clearTimer(args: args);
            break;
        case "clearInterval":
            clearTimer(args: args);
            break;
        default:
            break;
        }
        return "";
    }
    
    private func clearTimer(args: String) {
        if let data = args.data(using: String.Encoding.utf8, allowLossyConversion: true) {
            if let clearArgs = try? JSONDecoder().decode(ClearArgs.self, from: data) {
                if let timer = _timers[clearArgs.id] {
                    timer.stop();
                    _timers.removeValue(forKey: clearArgs.id);
                    NSLog("clearTimer=%d", clearArgs.id);
                }
            }
        }
    }
}
