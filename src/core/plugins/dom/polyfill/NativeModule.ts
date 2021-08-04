class NativeModule {
    _callbackMap: Map<number, any>;
    _callbackIds: number = 0;

    constructor() {
        this._callbackMap = new Map<number, any>();
    }

    get contextId(): number {
        return window.contextId;
    }

    makeNativeCallID(callback: any): number {
        const newId = this._callbackIds++;
        this._callbackMap.set(newId, callback);
        return newId;
    }

    queryNativeCallID(callID: number, keep: boolean = false): any | undefined {
        if (this._callbackMap.has(callID)) {
            const jsMethod = this._callbackMap.get(callID);
            return jsMethod;
        }
        return undefined;
    }

    deleteNativeCallID(callID: number) {
        this._callbackMap.delete(callID);
    }

    invokeNativeModule(
        moduleName: string,
        methodName: string,
        data: any,
        callback?: ModuleCallback,
    ) {
        return (
            window.__module__ &&
            window.__module__.invokeModule(moduleName, methodName, data, callback)
        );
    }
}

export default new NativeModule();
