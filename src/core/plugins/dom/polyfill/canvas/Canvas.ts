import Element from '../Element';
import CanvasRenderingContext2D from './CanvasRenderingContext2D';
import CanvasCommand from './CanvasCommand';
export default class Canvas extends Element {
    static TAG: string = 'canvas';
    _command: CanvasCommand;
    _context: CanvasRenderingContext2D;
    constructor() {
        super(Canvas.TAG);
        this._command = new CanvasCommand(this);
    }

    get commander() {
        return this._command;
    }

    getContext(type: string) {
        if (type.match(/2d/i)) {
            if (!this._context) {
                this._context = new CanvasRenderingContext2D(this);
            }
        } else {
            throw new Error('invalid arguments');
        }
        return this._context;
    }
}
