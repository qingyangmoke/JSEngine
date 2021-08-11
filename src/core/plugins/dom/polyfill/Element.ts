import ElementAttribute from './ElementAttribute';
import Node from './Node';
import Style from './Style';
import UICommand from './UICommand';
import UIEvent from './UIEvent';
import ElementCache from './ElementCache';
import ContainerElement from './ContainerElement';
const ID_STRING = 'id';
const CLASS_STRING = 'className';
export default class Element extends Node {
    static _elementsMap: Map<number, Element> = new Map<number, Element>();
    _parent: Element | null;
    _doc: HTMLDocument | null;
    _previousSibling: Element | null;
    _nextSibling: Element | null;

    _style: Style;
    _attributes: ElementAttribute;
    _class: string;
    _domId: string;

    _eventListeners: Map<string, Array<any>> = new Map<string, Array<any>>();
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

    get parentElement(): ContainerElement | null {
        return this.parentNode as ContainerElement;
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
        return `<${
            this.tagName
        } ${this._attributes.toString()} style="${this._style.toString()}"></${this.tagName}>`;
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

    get width(): number {
        return parseFloat(this.getAttribute('width'));
    }

    set width(value: number | string) {
        this.setAttribute('width', value);
    }

    get height(): number {
        return parseFloat(this.getAttribute('height'));
    }

    set height(value: number | string) {
        this.setAttribute('height', value);
    }

    constructor(tagName: string, nodeType: number = Node.ELEMENT_NODE) {
        super(tagName, nodeType);
        this._style = new Style(this);
        this._attributes = new ElementAttribute(this);
        ElementCache.registerElement(this);
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

    destroy() {
        ElementCache.unregisterElement(this);
    }

    addEventListener(
        type: string,
        listener: Function,
        options?: boolean | AddEventListenerOptions,
    ): void {
        if (typeof listener !== 'function') {
            return;
        }
        if (!this._eventListeners.has(type)) {
            this._eventListeners.set(type, []);
        }
        const events = this._eventListeners.get(type);
        events?.push({
            listener,
            options,
        });
    }

    dispatchEvent(event: UIEvent): boolean {
        if (!this._eventListeners.has(event.type)) {
            return false;
        }
        const events = this._eventListeners.get(event.type);
        if (events) {
            events.forEach((e) => {
                e.listener(event);
            });
        }
        return false;
    }

    removeEventListener(
        type: string,
        callback: EventListenerOrEventListenerObject | null,
        options?: EventListenerOptions | boolean,
    ): void {
        if (!this._eventListeners.has(type)) {
            return;
        }
        if (!callback) {
            this._eventListeners.set(type, []);
            return;
        }
        const events = this._eventListeners.get(type)?.filter((e) => e.listener === callback) || [];
        this._eventListeners.set(type, events);
    }
}
