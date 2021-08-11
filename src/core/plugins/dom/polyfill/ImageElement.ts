import Element from './Element';
import Node from './Node';
import UIEvent from './UIEvent';
class ImageElement extends Element {
    static TAG: string = 'img';
    _onload: Function | undefined;
    _onerror: Function | undefined;
    constructor(width: number | undefined, height: number | undefined) {
        super(ImageElement.TAG, Node.ELEMENT_NODE);
        if (width && width !== 0) this.setAttribute('width', width);
        if (height && height !== 0) this.setAttribute('height', height);
    }

    get src(): string {
        return this.getAttribute('src');
    }

    set src(value: string) {
        this.setAttribute('src', value);
    }

    receiveCommand(command: string, args: any) {
        super.receiveCommand(command, args);
    }

    set onload(value: Function | undefined) {
        this._onload = value;
    }

    get onload(): Function | undefined {
        return this._onload;
    }

    set onerror(value: Function | undefined) {
        this._onerror = value;
    }

    dispatchEvent(event: UIEvent): boolean {
        switch (event.type) {
            case 'error':
                if (this.onerror) {
                    this.onerror(event);
                }
                break;
            case 'load':
                if (this.onload) {
                    this.onload(event);
                }
                break;
        }
        return super.dispatchEvent(event);
    }
}

export default ImageElement;
