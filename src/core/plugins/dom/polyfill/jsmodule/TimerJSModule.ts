import NativeModule from '../NativeModule';
import JSModule from './JSModule';

const TIMER_SET_TIMEOUT: string = 'setTimeout';
const TIMER_CLEAR_TIMEOUT: string = 'clearTimeout';
const TIMER_SET_INTERVAL: string = 'setInterval';
const TIMER_CLEAR_INTERVAL: string = 'clearInterval';
const TIMER_NATIVE_MODULE_NAME: string = 'JSMTimer';
const TIMER_MODULE_NAME: string = 'JSMTimer';

export default class TimerJSModule extends JSModule {
    constructor() {
        super(TIMER_MODULE_NAME);
    }

    static setTimeout(callback: Function, delay: number): number {
        const id = NativeModule.makeNativeCallID({
            moduleName: TIMER_MODULE_NAME,
            type: TIMER_SET_TIMEOUT,
            callback,
        });
        NativeModule.invokeNativeModule(TIMER_NATIVE_MODULE_NAME, TIMER_SET_TIMEOUT, {
            id,
            delay,
        });
        return id;
    }

    static clearTimeout(id: number) {
        const data = NativeModule.queryNativeCallID(id);
        if (data && data.moduleName === TIMER_MODULE_NAME && data.type === TIMER_SET_TIMEOUT) {
            NativeModule.deleteNativeCallID(id);
        }
        NativeModule.invokeNativeModule(TIMER_NATIVE_MODULE_NAME, TIMER_CLEAR_TIMEOUT, {
            id: id,
        });
    }

    static setInterval(callback: Function, interval: number): number {
        const id = NativeModule.makeNativeCallID({
            moduleName: TIMER_MODULE_NAME,
            type: TIMER_SET_INTERVAL,
            callback,
        });
        NativeModule.invokeNativeModule(TIMER_NATIVE_MODULE_NAME, TIMER_SET_INTERVAL, {
            id,
            interval,
        });
        return id;
    }

    static clearInterval(id: number) {
        const data = NativeModule.queryNativeCallID(id);
        if (data && data.moduleName === TIMER_MODULE_NAME && data.type === TIMER_SET_INTERVAL) {
            NativeModule.deleteNativeCallID(id);
        }
        NativeModule.invokeNativeModule(TIMER_NATIVE_MODULE_NAME, TIMER_CLEAR_INTERVAL, {
            id: id,
        });
    }

    timerCallback(args: string) {
        console.log('timerCallback', args);
        const json = JSON.parse(args);
        const data = NativeModule.queryNativeCallID(json.id);
        if (data && data.moduleName === this.moduleName) {
            if (data.type === TIMER_SET_TIMEOUT) {
                NativeModule.deleteNativeCallID(json.id);
            }
            data.callback();
        }
    }
}
