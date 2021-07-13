import Element from './Element';
import Node from './Node';
class ImageElement extends Element {
    static TAG: string = 'img';
    constructor(width: number | undefined, height: number | undefined) {
        super(ImageElement.TAG, Node.ELEMENT_NODE);
        if (width || width === 0) this.setAttribute('width', width);
        if (height || height === 0) this.setAttribute('height', height);
    }

    receiveCommand(command: string, args: any) {
        super.receiveCommand(command, args);
    }
    
    onLoad(args: any) {

    }
}

export default ImageElement;
