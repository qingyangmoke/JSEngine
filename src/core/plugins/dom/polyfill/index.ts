import document from './Document';
import localStorage from './localStorage';
import memoryStorage from './memoryStorage';
import navigator from './navigator';

function defineGlobalProperty(key: string, value: any) {
    // Object.defineProperty(window, key, {
    //     value: value,
    //     enumerable: true,
    //     writable: false,
    //     configurable: false,
    // });
    window[key] = value;
}

defineGlobalProperty('document', document);
defineGlobalProperty('navigator', navigator);
defineGlobalProperty('memoryStorage', memoryStorage);
defineGlobalProperty('localStorage', localStorage);