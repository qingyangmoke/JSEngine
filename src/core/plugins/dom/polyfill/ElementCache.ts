import ContainerElement from './ContainerElement';
import DivElement from './DivElement';
import Element from './Element';
import Node from './Node';
import ImageElement from './ImageElement';
import Canvas from './canvas/Canvas';

class ElementCache {
    _elementMap: Map<number, Element>;
    constructor() {
        this._elementMap = new Map<number, Element>();
    }

    registerElement(element: Element) {
        this._elementMap.set(element.uniqueId, element);
    }

    unregisterElement(element: Element) {
        this._elementMap.delete(element.uniqueId);
    }

    getElement(uniqueId: number): Element | undefined {
        return this._elementMap.get(uniqueId);
    }
}

export default new ElementCache();
