import ContainerElement from './ContainerElement';
import DivElement from './DivElement';
import Element from './Element';
import Node from './Node';
import ImageElement from './ImageElement';

class ElementFactory {
    _map: Map<string, Element>;

    constructor() {
        this._map = new Map();
        this.registerElement(DivElement.TAG, DivElement);
        this.registerElement(ImageElement.TAG, ImageElement);
    }

    registerElement(tagName: string, type: any) {
        this._map.set(tagName, type);
    }

    createElement(tagName: string): Element {
        if (this._map.has(tagName)) {
            const Element = this._map.get(tagName) as any;
            return new Element(tagName);
        }
        return new ContainerElement(tagName, Node.ELEMENT_NODE);
    }
}

export default new ElementFactory();
