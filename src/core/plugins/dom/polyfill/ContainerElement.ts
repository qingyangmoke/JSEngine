import Element from './Element';
import UICommand from './UICommand';
import Node from './Node';
export default class Container extends Element {
    _firstChild: Element | null;
    _lastChild: Element | null;
    constructor(tagName: string, nodeType: number = Node.ELEMENT_NODE) {
        super(tagName, nodeType);
    }

    get childNodes(): Array<Element> {
        const result: Array<Element> = [];
        let node = this.firstChild;
        while (node) {
            result.push(node);
            node = node.nextSibling;
        }
        return result;
    }

    get firstChild(): Element | null {
        return this._firstChild;
    }

    get lastChild(): Element | null {
        return this._lastChild;
    }

    iteratorChild(parentNode: Element, iterator: (node: Element) => boolean | void): boolean {
        let ptr = (parentNode as Container).firstChild;
        while (ptr) {
            if (iterator(ptr)) {
                return true;
            }
            if (this.iteratorChild(ptr, iterator) === true) {
                return true;
            }
            ptr = ptr.nextSibling as Element;
        }
        return false;
    }

    getElementsByClassName(className: string): Array<Element> {
        const result: Array<Element> = [];
        this.iteratorChild(this, (node: Element): boolean => {
            if (node.className === className) {
                result.push(node);
            }
            return false;
        });
        return result;
    }

    getElementsByTagName(tagName: string): Array<Element> {
        const result: Array<Element> = [];
        this.iteratorChild(this, (node: Element): boolean | void => {
            if (node.nodeName === tagName) {
                result.push(node);
            }
            return false;
        });
        return result;
    }

    appendChild(newChild: Element): Element {
        if (this._lastChild) {
            this._lastChild.nextSibling = newChild;
            newChild.previousSibling = this._lastChild;
            newChild.nextSibling = null;
        } else {
            this._firstChild = newChild;
            this._lastChild = newChild;
            this._firstChild.previousSibling = null;
            this._firstChild.nextSibling = null;
        }
        newChild.ownerDocument = this._doc;
        newChild.parentNode = this;
        UICommand.sendCommand(UICommand.INSERT_CHILD, {
            uniqueId: this.uniqueId,
            newChild: {
                uniqueId: newChild.uniqueId,
            },
            refChild: {
                uniqueId: this.lastChild?.uniqueId || '',
            },
        });
        return newChild;
    }

    contains(other: Element | null): boolean {
        let exists = false;
        let node = this._firstChild;
        while (node) {
            if (node === other) {
                exists = true;
                break;
            }
        }
        return exists;
    }

    copyNodeWidthoutChild(node: Element): Element {
        const newNode = new Element(node.nodeName, node.nodeType);
        newNode.ownerDocument = node.ownerDocument;
        return newNode;
    }

    cloneNode(deep: boolean = false): Element {
        const newNode = this.copyNodeWidthoutChild(this) as Container;
        if (!deep) {
            newNode._firstChild = this._firstChild;
            newNode._lastChild = this._lastChild;
        } else {
            if (this._firstChild) {
                newNode._firstChild = this.copyNodeWidthoutChild(this.firstChild as Element);
                newNode._lastChild = this._firstChild;
                let oldChildNode = this._firstChild.nextSibling;
                let newChildNode = newNode._firstChild;
                while (oldChildNode) {
                    newChildNode.nextSibling = this.copyNodeWidthoutChild(oldChildNode);
                    newNode._lastChild = newChildNode.nextSibling;
                    oldChildNode = oldChildNode.nextSibling;
                }
            }
        }
        return newNode;
    }

    insertBefore(newChild: Element, refChild?: Element): Element {
        if (refChild) {
            newChild.nextSibling = refChild.nextSibling;
            newChild.previousSibling = refChild;
            newChild.ownerDocument = this.ownerDocument;
            refChild.nextSibling = newChild;
            newChild.parentNode = this;
        } else {
            this.appendChild(newChild);
        }
        UICommand.sendCommand(UICommand.INSERT_CHILD, {
            uniqueId: this.uniqueId,
            newChild: {
                uniqueId: newChild.uniqueId,
            },
            refChild: {
                uniqueId: refChild?.uniqueId || '',
            },
        });
        return newChild;
    }

    _removeFromChainTree(oldChild: Element) {
        if (oldChild.previousSibling) {
            oldChild.previousSibling.nextSibling = oldChild.nextSibling;
            if (oldChild === this._lastChild) {
                this._lastChild = oldChild.previousSibling;
            }
        } else if (oldChild.nextSibling) {
            oldChild.nextSibling.previousSibling = null;
            if (oldChild === this._firstChild) {
                this._firstChild = oldChild.nextSibling;
            }
        }
        oldChild.nextSibling = null;
        oldChild.previousSibling = null;
    }

    removeChild(oldChild: Element): Element {
        this._removeFromChainTree(oldChild);
        oldChild.parentNode = null;
        UICommand.sendCommand(UICommand.REMOVE_CHILD, {
            uniqueId: this.uniqueId,
            oldChild: {
                uniqueId: oldChild.uniqueId,
            },
        });
        return oldChild;
    }

    replaceChild(newChild: Element, oldChild: Element): Element | null {
        if (newChild.parentNode === this) {
            this._removeFromChainTree(newChild);
        }

        newChild.previousSibling = oldChild.previousSibling;
        newChild.nextSibling = oldChild.nextSibling;
        newChild.parentNode = this;
        newChild.ownerDocument = this.ownerDocument;
        UICommand.sendCommand(UICommand.REPLACE_CHILD, {
            uniqueId: this.uniqueId,
            newChild: {
                uniqueId: newChild.uniqueId,
            },
            oldChild: {
                uniqueId: oldChild.uniqueId,
            },
        });
        return newChild;
    }
}
