import Element from './Element';
import ContainerElement from './ContainerElement';
import BodyElement from './BodyElement';
import Node from './Node';
import ElementFactory from './ElementFactory';
import UIEvent from './UIEvent';
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

    get title(): number {
        return parseFloat(this.getAttribute('title'));
    }

    set title(value: number | string) {
        this.setAttribute('title', value);
    }

    createElement(tagName: string): Element {
        return ElementFactory.createElement(tagName);
    }

    registerElementType(tagName: string, type: any) {
        ElementFactory.registerElementType(tagName, type);
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

    dispatchEvent(event: UIEvent): boolean {
        switch (event.type) {
            case 'resize':
                if (event.target === this && event.data) {
                    const { width, height } = event.data;
                    // @ts-ignore
                    window.innerWidth = width;
                    // @ts-ignore
                    window.innerHeight = height;
                    console.log('window.resize', window.innerWidth, window.innerHeight);
                }
                break;
                
        }
        return super.dispatchEvent(event);
    }
}
export default new Document();
