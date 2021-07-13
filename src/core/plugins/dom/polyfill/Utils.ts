export function nativeCodify(func: any) {
    
    Object.keys(func.prototype).forEach((key) => {
        const value = func.prototype[key];
        if (typeof value === 'function') {
            value.toString = toNativeCode;
        }
    });
}

function toNativeCode() {}
