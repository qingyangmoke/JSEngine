import Element from './Element';
import ContainerElement from './ContainerElement';
import BodyElement from './BodyElement';
import Node from './Node';
import ElementFactory from './ElementFactory';
class Document extends ContainerElement {
    _body: BodyElement;
    constructor() {
        super('document', Node.DOCUMENT_NODE);
        this._body = new BodyElement();
        this.defineAttribute(['title']);
    }

    get uniqueId() {
        return 0;
    }
 
    get body(): BodyElement {
        return this._body;
    }

    createElement(tagName: string): Element {
        return ElementFactory.createElement(tagName);
    }

    registerElement(tagName: string, type: any) {
        ElementFactory.registerElement(tagName, type);
    }

    getElementById(id: string) {
        let element;
        this.iteratorChild(this, (node: Element): boolean | void => {
            if (node.id === id) {
                element = node;
                return true;
            }
        });
        return element;
    }
}
export default new Document();
