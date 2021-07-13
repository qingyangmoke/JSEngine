import Element from './Element';
import UICommand from './UICommand';
const PROXY_SYMBOL = Symbol('proxy');
export default class Style {
    _style = {};
    _element: Element;

    get style() {
        return this._style;
    }

    set style(value: any) {
        this._proxyStyle({ ...value });
        UICommand.sendCommand(UICommand.SET_STYLE, {
            uniqueId: this.uniqueId,
            style: this.style,
            replace: 1,
        });
    }

    get uniqueId() {
        return this._element.uniqueId;
    }

    constructor(parent: Element) {
        this._element = parent;
        this._proxyStyle({});
    }

    _proxyStyle(style: any) {
        if (this._style[PROXY_SYMBOL]) {
            return;
        }
        const uniqueId = this.uniqueId;
        this._style = new Proxy(style, {
            defineProperty(target: any, prop: string, oDesc: PropertyDescriptor): boolean {
                // 禁用 defineProperty
                return false;
            },
            deleteProperty(target: any, prop: string | symbol): boolean {
                delete target[prop];
                if (typeof prop !== 'symbol') {
                    UICommand.sendCommand(UICommand.SET_STYLE, {
                        uniqueId,
                        style: target,
                        replace: 1,
                    });
                }
                return true;
            },
            set(target: any, prop: string | symbol, value: any, receiver: any): boolean {
                target[prop] = value;
                if (typeof prop !== 'symbol') {
                    UICommand.sendCommand(UICommand.SET_STYLE, {
                        uniqueId,
                        style: {
                            prop: value,
                        },
                    });
                }
                return true;
            },
        });
        this._style[PROXY_SYMBOL] = true;
    }

    toString() {
        return Object.keys(this._style).map((e) => `${e}=${this._style[e]};`);
    }
}
