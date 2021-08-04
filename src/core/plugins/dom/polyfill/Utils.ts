export function nativeCodify(func: any) {
    Object.keys(func.prototype).forEach((key) => {
        const value = func.prototype[key];
        if (typeof value === 'function') {
            value.toString = toNativeCode;
        }
    });
}

function toNativeCode() {}

export function defineGlobalProperty(key: string, value: any) {
    // Object.defineProperty(window, key, {
    //     value: value,
    //     enumerable: true,
    //     writable: false,
    //     configurable: false,
    // });
    window[key] = value;
}
