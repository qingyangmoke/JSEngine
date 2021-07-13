import { nativeCodify } from './utils';

let _uniqueIdSeed = 100;
export default class Node {
    static ATTRIBUTE_NODE: number = 2;
    /**
     * node is a CDATASection node.
     */
    static CDATA_SECTION_NODE: number = 4;
    /**
     * node is a Comment node.
     */
    static COMMENT_NODE: number = 8;
    /**
     * node is a DocumentFragment node.
     */
    static DOCUMENT_FRAGMENT_NODE: number = 11;
    /**
     * node is a document.
     */
    static DOCUMENT_NODE: number = 9;

    /**
     * Set when other is a descendant of node.
     */
    static DOCUMENT_POSITION_CONTAINED_BY: number = 16;
    /**
     * Set when other is an ancestor of node.
     */
    static DOCUMENT_POSITION_CONTAINS: number = 8;
    /**
     * Set when node and other are not in the same tree.
     */
    static DOCUMENT_POSITION_DISCONNECTED: number = 1;
    /**
     * Set when other is following node.
     */
    static DOCUMENT_POSITION_FOLLOWING: number = 4;

    static DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC: number = 32;
    /**
     * Set when other is preceding node.
     */
    static DOCUMENT_POSITION_PRECEDING: number = 2;
    /**
     * node is a doctype.
     */
    static DOCUMENT_TYPE_NODE: number = 10;
    /**
     * node is an element.
     */
    static ELEMENT_NODE: number = 1;
    static ENTITY_NODE: number = 6;
    static ENTITY_REFERENCE_NODE: number = 5;
    static NOTATION_NODE: number = 12;
    /**
     * node is a ProcessingInstruction node.
     */
    static PROCESSING_INSTRUCTION_NODE: number = 7;
    /**
     * node is a Text node.
     */
    static TEXT_NODE: number = 3;

    _nodeType: number = Node.ELEMENT_NODE;
    _nodeName: string;

    _uniqueId: number;
    constructor(nodeName: string, nodeType: number) {
        this._nodeName = nodeName;
        this._nodeType = nodeType;
        this._uniqueId = _uniqueIdSeed++;
    }
    get nodeName() {
        return this._nodeName;
    }
    get nodeType(): number {
        return this._nodeType;
    }
    get uniqueId(): number {
        return this._uniqueId;
    }

    get baseURI(): string {
        return '';
    }
}

