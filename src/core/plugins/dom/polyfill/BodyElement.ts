import ContainerElement from './ContainerElement';
import Node from './Node';
class BodyElement extends ContainerElement {
    get uniqueId() {
        return 1;
    }
    constructor() {
        super('body', Node.ELEMENT_NODE);
    }
}
export default BodyElement;
