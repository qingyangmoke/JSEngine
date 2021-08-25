class UICommand {
    static MODULE_NAME = 'UI';
    // 设置style样式
    static SET_STYLE: string = 'setStyle';
    // 删除style样式
    static REMOVE_STYLE: string = 'removeStyle';
    // 创建对象
    static CREATE_ELEMENT: string = 'createElement';
    // 新增属性
    static SET_ATTRIBUTE: string = 'setAttribute';
    // 获取属性
    static GET_ATTRIBUTE: string = 'getAttribute';
    // 删除属性
    static REMOVE_ATTRIBUTE: string = 'removeAttribute';
    // 添加child
    static INSERT_CHILD: string = 'insertChild';
    // 删除child
    static REMOVE_CHILD: string = 'removeChild';
    // 替换child
    static REPLACE_CHILD: string = 'replaceChild';
    // 滚动
    static SCROLL_TO: string = 'scrollTo';
    // TOAST 弱提示
    static TOAST: string = 'toast';
    // alert 强提示
    static ALERT: string = 'alert';
    /***
     * 发送UI指令
     */
    static sendCommand(command: string, data: any, callback?: ModuleCallback): any {
        console.log(
            `sendCommand command=${command}`,
            JSON.stringify(data),
            typeof window.__module__,
        );
        return (
            window.__module__ &&
            window.__module__.invokeModule(UICommand.MODULE_NAME, command, data, callback)
        );
    }

    /**
     * toast弱提示
     * @param {String} message - 消息
     * @param {Number} [duration=2000] - 事件
     */
    static toast(message: string, duration = 2000) {
        UICommand.sendCommand(UICommand.TOAST, {
            message,
            duration,
        });
    }
}

export default UICommand;
