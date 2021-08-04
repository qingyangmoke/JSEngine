import NativeModule from '../NativeModule';

export default class JSModule {
    _moduleName: string;
    constructor(moduleName: string) {
        this._moduleName = moduleName;
    }
    get moduleName() {
        return this._moduleName;
    }
}
