import UICommand from '../UICommand';
import CanvasTextMetrics from './CanvasTextMetrics';
import Canvas from './Canvas';
export default class CanvasCommand {
    static MODULE_NAME = 'canvas';
    static BATCH_COMMAND = 'batchCmd';
    static MEASURE_TEXT_COMMAND = 'measureText';
    static CREATE_CONTEXT_COMMAND = 'createContext';
    _commands: Array<{ command: string; data: any }> = [];
    _canvas: Canvas;

    constructor(canvas: Canvas) {
        this._canvas = canvas;
        // setInterval(() => {
        //     this.render();
        // }, 1000 / 60);
    }

    pushCommand(command: string, data?: any): any {
        this._commands.push({
            command,
            data,
        });
    }

    _args(args: any = {}) {
        args.uniqueId = this._canvas.uniqueId;
        return args;
    }

    createContext(type: string) {
        this.sendCommand(CanvasCommand.CREATE_CONTEXT_COMMAND, {
            type,
        });
    }

    measureText(text: string): CanvasTextMetrics {
        const result = this.sendCommand(CanvasCommand.MEASURE_TEXT_COMMAND, {
            text,
        });
        const a = JSON.parse(result);
        return new CanvasTextMetrics(a.width);
    }

    sendCommand(command: string, data: any, callback?: ModuleCallback): any {
        return (
            window.__module__ &&
            window.__module__.invokeModule(
                CanvasCommand.MODULE_NAME,
                command,
                this._args(data || {}),
                callback,
            )
        );
    }

    flush() {
        this.sendCommand(CanvasCommand.BATCH_COMMAND, {
            commands: this._commands,
            length: this._commands.length,
        });
        this._commands = [];
    }

    render() {
        if (this._commands.length > 0) {
            this.flush();
        }
    }
}
