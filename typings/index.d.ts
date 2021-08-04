type ModuleCallback = (errorCode: number, result: string) => void;
interface Window {
    contextId: number,
    __module__: {
        invokeModule: (
            moduleName: string,
            method: string,
            data: any,
            callback?: ModuleCallback,
        ) => string;
    };
}
