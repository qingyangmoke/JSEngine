import Element from './Element';
import UICommand from './UICommand';
const KEY_MAPS = {
    class: 'className',
};
export default class ElementAttribute {
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
        key = this[this._keyModify(key)];
        return this._attributes[key];
    }

    setAttribute(key: string, value: any): void {
        key = this._keyModify(key);
        this._attributes[key] = value;
        UICommand.sendCommand(UICommand.SET_ATTRIBUTE, {
            uniqueId: this.uniqueId,
            attribute: {
                [key]: value,
            },
        });
    }

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
