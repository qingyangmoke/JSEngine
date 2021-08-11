/** An event which takes place in the DOM. */
import Element from './Element';
export default class UIEvent {
    _bubbles: boolean = false;
    /**
     * Returns true or false depending on how event was initialized. True if event goes through its target's ancestors in reverse tree order, and false otherwise.
     */
    get bubbles(): boolean {
        return this._bubbles;
    }
    _cancelable: boolean = false;
    /**
     * Returns true or false depending on how event was initialized. Its return value does not always carry meaning, but true can indicate that part of the operation during which event was dispatched, can be canceled by invoking the preventDefault() method.
     */
    get cancelable(): boolean {
        return this._cancelable;
    }
    /**
     * Returns true or false depending on how event was initialized. True if event invokes listeners past a ShadowRoot node that is the root of its target, and false otherwise.
     */
    get composed(): boolean {
        return false;
    }

    _currentTarget: Element | undefined;
    /**
     * Returns the object whose event listener's callback is currently being invoked.
     */
    get currentTarget(): Element | undefined {
        return this._currentTarget;
    }

    _defaultPrevented: boolean = false;
    /**
     * Returns true if preventDefault() was invoked successfully to indicate cancelation, and false otherwise.
     */
    get defaultPrevented(): boolean {
        return this._defaultPrevented;
    }
    /**
     * Returns the event's phase, which is one of NONE, CAPTURING_PHASE, AT_TARGET, and BUBBLING_PHASE.
     */
    // readonly eventPhase: number;
    /**
     * Returns true if event was dispatched by the user agent, and false otherwise.
     */
    get isTrusted(): boolean {
        return true;
    }

    returnValue: boolean;

    _target: Element | undefined = undefined;
    /**
     * Returns the object to which event is dispatched (its target).
     */
    get target(): Element | undefined {
        return this._target;
    }

    _timeStamp: number = Date.now();
    get timeStamp(): number {
        return this._timeStamp;
    }

    _type: string;
    /**
     * Returns the type of event, e.g. "click", "hashchange", or "submit".
     */
    get type(): string {
        return this._type;
    }

    _data: any;
    get data(): any {
        return this.data;
    }
    set data(value: any) {
        this._data = value;
    }
    /**
     * Returns the invocation target objects of event's path (objects on which listeners will be invoked), except for any nodes in shadow trees of which the shadow root's mode is "closed" that are not reachable from event's currentTarget.
     */
    // composedPath(): EventTarget[] {
    //   return null;
    // }
    initEvent(type: string, bubbles?: boolean, cancelable?: boolean): void {
        this._type = type;
        this._bubbles = bubbles ?? false;
        this._cancelable = cancelable ?? false;
    }
    /**
     * If invoked when the cancelable attribute value is true, and while executing a listener for the event with passive set to false, signals to the operation that caused event to be dispatched that it needs to be canceled.
     */
    preventDefault(): void {}
    /**
     * Invoking this method prevents event from reaching any registered event listeners after the current one finishes running and, when dispatched in a tree, also prevents event from reaching any other objects.
     */
    stopImmediatePropagation(): void {}
    /**
     * When dispatched in a tree, invoking this method prevents event from reaching any objects other than the current object.
     */
    stopPropagation(): void {}
}
