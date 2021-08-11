import ContainerElement from './ContainerElement';
import Node from './Node';
import UICommand from './UICommand';

export default class ScrollerElement extends ContainerElement {
    static TAG: string = 'scroller';
    constructor() {
        super(ScrollerElement.TAG, Node.ELEMENT_NODE);
    }

    scrollTo(x: number, y: number) {
        UICommand.sendCommand(UICommand.SCROLL_TO, {
            uniqueId: this.uniqueId,
            x,
            y,
        });
    }
}
