import document from './Document';
import localStorage from './localStorage';
import memoryStorage from './memoryStorage';
import navigator from './navigator';
import { defineGlobalProperty } from './Utils';
import JSModuleManager from './jsmodule/JSModuleManager';
import TimerJSModule from './jsmodule/TimerJSModule';
import JSModule from './jsmodule/JSModule';

defineGlobalProperty('document', document);
defineGlobalProperty('navigator', navigator);
defineGlobalProperty('memoryStorage', memoryStorage);
defineGlobalProperty('localStorage', localStorage);

defineGlobalProperty('setTimeout', TimerJSModule.setTimeout);
defineGlobalProperty('setInterval', TimerJSModule.setInterval);
defineGlobalProperty('clearInterval', TimerJSModule.clearInterval);
defineGlobalProperty('clearTimeout', TimerJSModule.clearTimeout);

defineGlobalProperty('JSModule', JSModule);

defineGlobalProperty('registerJSModule', function registerJSModule(module: JSModule) {
    JSModuleManager.registerJSModule(module);
});
