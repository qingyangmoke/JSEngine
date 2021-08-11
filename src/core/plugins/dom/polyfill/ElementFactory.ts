import ContainerElement from './ContainerElement';
import DivElement from './DivElement';
import Element from './Element';
import Node from './Node';
import ImageElement from './ImageElement';
import Canvas from './canvas/Canvas';
import ScrollerElement from './ScrollerElement';

class ElementFactory {
    _typeMap: Map<string, Element>;
    constructor() {
        this._typeMap = new Map();
        this.registerElementType(DivElement.TAG, DivElement);
        this.registerElementType(ImageElement.TAG, ImageElement);
        this.registerElementType(Canvas.TAG, Canvas);
        this.registerElementType(ScrollerElement.TAG, ScrollerElement);
    }

    registerElementType(tagName: string, type: any) {
        this._typeMap.set(tagName, type);
    }

    createElement(tagName: string): Element {
        if (this._typeMap.has(tagName)) {
            const Element = this._typeMap.get(tagName) as any;
            return new Element();
        }
        return new ContainerElement(tagName, Node.ELEMENT_NODE);
    }
}

export default new ElementFactory();
