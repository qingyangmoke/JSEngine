import Canvas from './Canvas';
import Element from '../Element';
import CanvasGradient from './CanvasGradient';
import CanvasTextMetrics from './CanvasTextMetrics';
import CanvasImageSource from './CanvasImageSource';
import CanvasImageData from './CanvasImageData';
import CanvasCommand from './CanvasCommand';

const Repetition = {
    repeat: 'repeat',
    repeatX: 'repeat-x',
    repeatY: 'repeat-y',
    noRepeat: 'no-repeat',
};

class Color {
    r = 0;
    g = 0;
    b = 0;
    a = 255;

    constructor(r: number, g: number, b: number, a: number) {
        this.setRgba(r, g, b, a);
    }

    setRgba(r: number, g: number, b: number, a: number) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }

    setColor(color: string): void {
        // 如果是rgb颜色表示
        if (/^(rgba|RGBA)/.test(color)) {
            var aColor = color.replace(/(?:\(|\)|rgba|RGBA)*/g, '').split(',');
            if (aColor.length !== 4) {
                throw new Error('invalid color');
            }
            this.r = Number(aColor[0]) || 0;
            this.g = Number(aColor[1]) || 0;
            this.b = Number(aColor[2]) || 0;
            this.a =
                typeof aColor[3] === 'undefined'
                    ? 255
                    : Math.min(255, Math.round(Number(aColor[3]) * 255));
        } else if (/^(rgb|RGB)/.test(color)) {
            var aColor = color.replace(/(?:\(|\)|rgb|RGB)*/g, '').split(',');
            if (aColor.length !== 3) {
                throw new Error('invalid color');
            }
            this.r = Number(aColor[0]) || 0;
            this.g = Number(aColor[1]) || 0;
            this.b = Number(aColor[2]) || 0;
            this.a = 255;
        } else if (color.indexOf('#') === 0) {
            var aNum = color.substring(1).split('');
            if (aNum.length === 8) {
                this.a = parseInt(`${aNum[0]}${aNum[1]}`, 16);
                this.r = parseInt(`${aNum[2]}${aNum[3]}`, 16);
                this.g = parseInt(`${aNum[4]}${aNum[5]}`, 16);
                this.b = parseInt(`${aNum[6]}${aNum[7]}`, 16);
            } else if (aNum.length === 6) {
                this.r = parseInt(`${aNum[0]}${aNum[1]}`, 16);
                this.g = parseInt(`${aNum[2]}${aNum[3]}`, 16);
                this.b = parseInt(`${aNum[4]}${aNum[5]}`, 16);
                this.a = 255;
            } else if (aNum.length === 3) {
                this.r = parseInt(`${aNum[0]}${aNum[0]}`, 16);
                this.g = parseInt(`${aNum[1]}${aNum[1]}`, 16);
                this.b = parseInt(`${aNum[2]}${aNum[2]}`, 16);
                this.a = 255;
            } else {
                throw new Error('invalid color');
            }
        } else {
            throw new Error('invalid color');
        }
    }

    toString() {
        return `rgba(${this.r},${this.g},${this.b},${this.a / 255})`;
    }
}

export default class CanvasRenderingContext2D {
    _canvas: Canvas;
    _lineWidth: number = 1;
    _lineCap: string = 'butt'; // "butt", "round", "square".
    _lineJoin: string = 'bevel'; // "bevel", "round", and "miter"
    _miterLimit: number = 10;
    _lineDashOffset: number = 0;
    _antiAlias: boolean = true;
    _lineDash: [];
    _fillStyle: Color = new Color(0, 0, 0, 255);
    _strokeStyle: Color = new Color(0, 0, 0, 255);

    constructor(canvas: Canvas) {
        this._canvas = canvas;
        this.cmd.createContext('2d');
    }

    get canvas() {
        return this._canvas;
    }

    get cmd() {
        return this.canvas.commander;
    }

   
    get lineWidth() {
        return this._lineWidth;
    }
    set lineWidth(value: number) {
        this._lineWidth = value;
        this.cmd.pushCommand('lineWidth', {
            value: value,
        });
    }
    get lineCap() {
        return this._lineCap;
    }
    set lineCap(value: string) {
        this._lineCap = value;
        this.cmd.pushCommand('lineCap', {
            value: value,
        });
    }
    get lineJoin() {
        return this._lineJoin;
    }
    set lineJoin(value: string) {
        this._lineJoin = value;
        this.cmd.pushCommand('lineJoin', {
            value: value,
        });
    }
    get miterLimit() {
        return this._miterLimit;
    }
    set miterLimit(value: number) {
        this._miterLimit = value;
        this.cmd.pushCommand('miterLimit', {
            value: value,
        });
    }
    get lineDashOffset() {
        return this._lineDashOffset;
    }
    set lineDashOffset(value: number) {
        this._lineDashOffset = value;
        this.cmd.pushCommand('lineDashOffset', {
            value: value,
        });
    }

    get antiAlias() {
        return this._antiAlias;
    }

    set antiAlias(value: boolean) {
        this._antiAlias = value;
        this.cmd.pushCommand('antiAlias', {
            value: value ? 1 : 0,
        });
    }

    get fillStyle(): string {
        return this._fillStyle.toString();
    }

    set fillStyle(value: string) {
        this._fillStyle.setColor(value);
        this.cmd.pushCommand('fillStyle', {
            r: this._fillStyle.r,
            g: this._fillStyle.g,
            b: this._fillStyle.b,
            a: this._fillStyle.a,
        });
    }

    get strokeStyle(): string {
        return this._strokeStyle.toString();
    }

    set strokeStyle(value: string) {
        this._strokeStyle.setColor(value);
        this.cmd.pushCommand('strokeStyle', {
            r: this._strokeStyle.r,
            g: this._strokeStyle.g,
            b: this._strokeStyle.b,
            a: this._strokeStyle.a,
        });
    }

    setAntiAlias(antiAlias: boolean) {
        this.antiAlias = antiAlias;
    }

    // state
    save(): void {
        this.cmd.pushCommand('save');
    }
    restore(): void {
        this.cmd.pushCommand('restore');
    }

    // transformations (default: transform is the identity matrix)
    scale(x: number, y: number) {
        this.cmd.pushCommand('scale', {
            x,
            y,
        });
    }
    rotate(angle: number) {
        this.cmd.pushCommand('rotate', {
            angle,
        });
    }
    translate(x: number, y: number) {
        this.cmd.pushCommand('translate', {
            x,
            y,
        });
    }
    transform(a: number, b: number, c: number, d: number, e: number, f: number) {
        this.cmd.pushCommand('transform', {
            a,
            b,
            c,
            d,
            e,
            f,
        });
    }
    setTransform(a: number, b: number, c: number, d: number, e: number, f: number) {
        this.cmd.pushCommand('setTransform', {
            a,
            b,
            c,
            d,
            e,
            f,
        });
    }
    // rects
    clearRect(x: number, y: number, w: number, h: number): void {
        this.cmd.pushCommand('clearRect', {
            x,
            y,
            w,
            h,
        });
    }
    fillRect(x: number, y: number, w: number, h: number): void {
        this.cmd.pushCommand('fillRect', {
            x,
            y,
            w,
            h,
        });
    }
    strokeRect(x: number, y: number, w: number, h: number): void {
        this.cmd.pushCommand('strokeRect', {
            x,
            y,
            w,
            h,
        });
    }

    // path API (see also CanvasPathMethods)
    beginPath(): void {
        this.cmd.pushCommand('beginPath');
    }
    fill() {
        this.cmd.pushCommand('fill');
    }
    stroke(): void {
        this.cmd.pushCommand('stroke');
    }
    drawFocusIfNeeded(element: Element): void {
        // this.cmd.pushCommand('drawFocusIfNeeded');
    }
    clip(): void {
        this.cmd.pushCommand('clip');
    }
    isPointInPath(x: number, y: number): boolean {
        return false;
    }
    moveTo(x: number, y: number): void {
        this.cmd.pushCommand('moveTo', { x, y });
    }
    lineTo(x: number, y: number): void {
        this.cmd.pushCommand('lineTo', { x, y });
    }
    quadraticCurveTo(cpx: number, cpy: number, x: number, y: number): void {
        this.cmd.pushCommand('quadraticCurveTo', { cpx, cpy, x, y });
    }
    bezierCurveTo(
        cp1x: number,
        cp1y: number,
        cp2x: number,
        cp2y: number,
        x: number,
        y: number,
    ): void {
        this.cmd.pushCommand('bezierCurveTo', { cp1x, cp1y, cp2x, cp2y, x, y });
    }
    arcTo(x1: number, y1: number, x2: number, y2: number, radius: number): void {
        this.cmd.pushCommand('arcTo', { x1, y1, x2, y2, radius });
    }
    rect(x: number, y: number, w: number, h: number): void {
        this.cmd.pushCommand('rect', { x, y, w, h });
    }
    arc(
        x: number,
        y: number,
        radius: number,
        startAngle: number,
        endAngle: number,
        counterclockwise: boolean = false,
    ): void {
        this.cmd.pushCommand('arc', { x, y, radius, startAngle, endAngle, counterclockwise });
    }
    closePath(): void {
        this.cmd.pushCommand('closePath');
    }

    // text (see also the CanvasDrawingStyles interface)
    fillText(text: string, x: number, y: number, maxWidth: number): void {
        this.cmd.pushCommand('fillText', { text, x, y, maxWidth });
    }

    strokeText(text: number, x: number, y: number, maxWidth: number): void {
        this.cmd.pushCommand('strokeText', { text, x, y, maxWidth });
    }

    measureText(text: string): CanvasTextMetrics {
        return this.cmd.measureText(text);
    }

    setLineDash(segments: []) {
        this._lineDash = segments;
        this.cmd.pushCommand('lineDash', { lineDash: segments });
    }

    getLineDash(): [] {
        return this._lineDash;
    }

    // drawing images
    // drawImage(image: CanvasImageSource, dx: number, dy: number): void;
    // drawImage(image: CanvasImageSource, dx: number, dy: number, dw: number, dh: number): void;
    // drawImage(
    //     image: CanvasImageSource,
    //     sx: number,
    //     sy: number,
    //     sw: number,
    //     sh: number,
    //     dx: number,
    //     dy: number,
    //     dw: number,
    //     dh: number,
    // ):
    // drawImage(
    //     image: CanvasImageSource,
    //     sx: number,
    //     sy: number,
    //     sw: number,
    //     sh: number,
    //     dx: number,
    //     dy: number,
    //     dw: number,
    //     dh: number,
    // ): void {
    //     this.cmd.pushCommand('drawImage', { image, sx, sy, sw, sh, dx, dy, dw, dh });
    // }
    drawImage(image: CanvasImageSource, ...rest: Array<number>): void {
        let sx, sy, sw, sh, dx, dy, dw, dh;
        if (rest.length === 2) {
            dx = rest[0];
            dy = rest[1];
        } else if (rest.length === 4) {
            dx = rest[0];
            dy = rest[1];
            dw = rest[2];
            dh = rest[3];
        } else if (rest.length === 8) {
            sx = rest[0];
            sy = rest[1];
            sw = rest[2];
            sh = rest[3];

            dx = rest[4];
            dy = rest[5];
            dw = rest[6];
            dh = rest[7];
        } else {
            throw new Error('参数错误');
        }
        this.cmd.pushCommand('drawImage', { textureId: 0, params: rest });
    }

    createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient {
        throw new Error('Not support');
    }

    createRadialGradient(
        x0: number,
        y0: number,
        r0: number,
        x1: number,
        y1: number,
        r1: number,
    ): CanvasGradient {
        throw new Error('Not support');
    }

    /**
     *
     * @param {CanvasImageSource} image
     * @param {string} repetition
     */
    createPattern(image: CanvasImageSource, repetition = Repetition.repeat): CanvasPattern {
        throw new Error('Not support');
    }

    // pixel manipulation 不支持
    createImageData(sw: number, sh: number): CanvasImageData {
        throw new Error('Not support');
    }

    // createImageData(imagedata: ImageData): CanvasImageData {
    //     throw new Error('Not support');
    // }

    getImageData(sx: number, sy: number, sw: number, sh: number): CanvasImageData {
        throw new Error('Not support');
    }
    putImageData(
        imagedata: CanvasImageData,
        dx: number,
        dy: number,
        dirtyX?: number,
        dirtyY?: number,
        dirtyWidth?: number,
        dirtyHeight?: number,
    ) {
        throw new Error('Not support');
    }
}
