import Element from './Element';
import UICommand from './UICommand';

const KEY_MAPS = {
    class: 'className',
};

export default class ElementAttribute {
    static NATIVE_ATTRIBUTES = ['width', 'height'];

    _attributes: Object;
    _element: Element;

    get uniqueId() {
        return this._element.uniqueId;
    }

    constructor(parent: Element) {
        this._element = parent;
        this._attributes = Object.create(null);
    }

    get keys() {
        return Object.keys(this._attributes);
    }

    _keyModify(key: string | symbol): string {
        return KEY_MAPS[key] || key;
    }

    getAttribute(key: string): string {
        key = this._keyModify(key);
        if (ElementAttribute.NATIVE_ATTRIBUTES.indexOf(key) !== -1) {
            return (
                UICommand.sendCommand(UICommand.GET_ATTRIBUTE, {
                    uniqueId: this.uniqueId,
                    key,
                }) ?? ''
            );
        } else {
            return this._attributes[key];
        }
    }

    setAttribute(key: string, value: any): void {
        key = this._keyModify(key);
        if (this._attributes[key] !== value) {
            this._attributes[key] = value;
            UICommand.sendCommand(UICommand.SET_ATTRIBUTE, {
                uniqueId: this.uniqueId,
                attribute: {
                    [key]: `${value}`,
                },
            });
        }
    }

    // /**
    //  *
    //  * @param {String} key - 一般是外部发生变化的时候进行处理
    //  * @param {String} value -
    //  */
    // setAttributeInner(key: string, value: any): void {
    //     key = this._keyModify(key);
    //     this._attributes[key] = value;
    // }

    removeAttribute(key: string): void {
        key = this._keyModify(key);
        if (Object.hasOwnProperty.call(this, key)) {
            delete this[key];
        }
        UICommand.sendCommand(UICommand.REMOVE_ATTRIBUTE, {
            uniqueId: this.uniqueId,
            key,
        });
    }

    toString() {
        return Object.keys(this._attributes).map((e) => `${e}="${this._attributes[e]}" `);
    }
}
