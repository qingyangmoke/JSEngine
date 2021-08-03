export default class CanvasTextMetrics {
    _w: number;
    constructor(width: number) {
        this._w = width;
    }
    get width(): number {
        return this._w;
    }
}
