import ContainerElement from './ContainerElement';
import Node from './Node';

export default class DivElement extends ContainerElement {
    static TAG: string = 'div';
    constructor() {
        super(DivElement.TAG, Node.ELEMENT_NODE);
    }
}
