import JSModule from './JSModule';
import TimerJSModule from './TimerJSModule';
import { defineGlobalProperty } from '../Utils';

class JSModuleManager {
    _moduleMap: Map<string, JSModule>;
    constructor() {
        this._moduleMap = new Map();
        this.registerJSModule(new TimerJSModule());
    }

    registerJSModule(module: JSModule) {
        if (window[module.moduleName]) {
            throw new Error(`module [${module.moduleName}] exists`);
        }
        this._moduleMap[module.moduleName] = module;
        defineGlobalProperty(module.moduleName, module);
    }
}

export default new JSModuleManager();
