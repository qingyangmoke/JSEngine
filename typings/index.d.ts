type ModuleCallback = (errorCode: number, result: string) => void;
interface Window {
    __module__: {
        invokeModule: (
            moduleName: string,
            method: string,
            data: any,
            callback?: ModuleCallback,
        ) => string;
    };
}
