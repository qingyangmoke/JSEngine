import ElementAttribute from './ElementAttribute';
import Node from './Node';
import Style from './Style';
import UICommand from './UICommand';
const ID_STRING = 'id';
const CLASS_STRING = 'className';
export default class Element extends Node {
    _parent: Element | null;
    _doc: HTMLDocument | null;
    _previousSibling: Element | null;
    _nextSibling: Element | null;

    _style: Style;
    _attributes: ElementAttribute;
    _class: string;
    _domId: string;
    get previousSibling(): Element | null {
        return this._previousSibling;
    }

    set previousSibling(value: Element | null) {
        this._previousSibling = value;
    }

    get nextSibling(): Element | null {
        return this._nextSibling;
    }

    set nextSibling(value: Element | null) {
        this._nextSibling = value;
    }

    get childNodes(): Array<Element> {
        return [];
    }

    get parentNode(): Element | null {
        return this._parent;
    }

    set parentNode(value: Element | null) {
        this._parent = value;
    }

    get style() {
        return this._style.style;
    }

    set style(value: any) {
        this._style.style = value;
    }

    get parentElement(): Node | null {
        return this.parentNode;
    }

    get tagName() {
        return this._nodeName;
    }

    get textContent(): string {
        return '';
    }

    get innerText(): string {
        return '';
    }

    get innerHTML(): string {
        return `<${this.tagName} ${this._attributes.toString()} style="${this._style.toString()}"></${this.tagName}>`;
    }

    get ownerDocument(): HTMLDocument | null {
        return this._doc;
    }

    set ownerDocument(value: HTMLDocument | null) {
        this._doc = value;
    }

    get isConnected(): boolean {
        return this.parentNode !== null;
    }

    get id(): string {
        return this.getAttribute(ID_STRING);
    }

    set id(value: string) {
        this.setAttribute(ID_STRING, value);
    }

    get className(): string {
        return this.getAttribute(CLASS_STRING);
    }

    set className(value: string) {
        this.setAttribute(ID_STRING, value);
    }

    constructor(tagName: string, nodeType: number = Node.ELEMENT_NODE) {
        super(tagName, nodeType);
        this._style = new Style(this);
        this._attributes = new ElementAttribute(this);
        UICommand.sendCommand(UICommand.CREATE_ELEMENT, {
            uniqueId: this.uniqueId,
            tagName: tagName,
        });
    }
    /**
     * @protected
     * @param {string | Array<string>} keys - 需要定义供外部使用的属性
     */
    defineAttribute(keys: string | Array<string>) {
        (typeof keys === 'string' ? [keys] : keys).forEach((key: string) => {
            Object.defineProperty(this, key, {
                get: () => {
                    return this.getAttribute(key);
                },
                set: (value: any) => {
                    this.setAttribute(key, value);
                },
            });
        });
    }

    getAttribute(key: string): string {
        return this._attributes.getAttribute(key);
    }

    setAttribute(key: string, value: any): void {
        this._attributes.setAttribute(key, value);
    }

    removeAttribute(key: string): void {
        this._attributes.removeAttribute(key);
    }

    cloneNode(deep: boolean = false): Element {
        const newNode = new Element(this.tagName, this.nodeType);
        newNode.ownerDocument = this.ownerDocument;
        return newNode;
    }

    receiveCommand(command: string, args: any) {
        if (typeof this[command] === 'function') {
            this[command](args);
        }
        console.log('command=', command, ',args=', args);
    }
}
