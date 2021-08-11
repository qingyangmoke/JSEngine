import NativeModule from '../NativeModule';
import UIEvent from '../UIEvent';
import Element from '../Element';
import JSModule from './JSModule';
import ElementCache from '../ElementCache';

const UI_EVENT_MODULE_NAME: string = 'JSMUIEvent';

export default class UIEventJSModule extends JSModule {
    constructor() {
        super(UI_EVENT_MODULE_NAME);
    }

    onNativeEvent(args: string) {
        console.log('onNativeEvent', args);
        const json = JSON.parse(args);
        const event = new UIEvent();
        event.initEvent(json.type, json.bubbles, json.cancelable);        
        const element: any = ElementCache.getElement(json.uniqueId);
        event._target = element;
        event.data = json.data;
        event._currentTarget = element;
        element?.dispatchEvent(event);
    }
}
