//
//  JSTimer.swift
//  ioscplus
//
//  Created by song on 2021/8/5.
//

import Foundation

class JSTimer {
    private var _id: Int32;
    private var _scope: JSEngineScope;
    private var _stopped: Bool = false;
    private weak var _timer: Timer?;
    public init(id: Int32, scope: JSEngineScope) {
        _id = id;
        _scope = scope;
        _stopped = false;
    }

    public func getScope() -> JSEngineScope {
        return _scope;
    }
    
    public func setTimeout(delay: Int32) {
        _timer?.invalidate();
        _timer = Timer.scheduledTimer(withTimeInterval: (Double(delay) / 1000), repeats: false, block: { (timer: Timer) in
            if(!self._stopped) {
                self._scope.invokeJSModule(moduleName: "JSMTimer", methodName: "timerCallback", args: String(format: "{\"id\": %d}", self._id));
                self.stop();
            }
        });
    }
    
    public func setInterval(interval: Int32) {
        _timer?.invalidate();
        _timer = Timer.scheduledTimer(withTimeInterval: (Double(interval) / 1000), repeats: true, block: { (timer: Timer) in
            if(!self._stopped) {
                self._scope.invokeJSModule(moduleName: "JSMTimer", methodName: "timerCallback", args: String(format: "{\"id\": %d}", self._id));
            }
        });
    }
    
    public func stop() {
        _stopped = true;
        _timer?.invalidate();
    }
}
