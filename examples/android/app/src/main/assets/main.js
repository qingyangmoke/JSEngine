console.log('javascript', 'hello world');

var toResult = window.__alita__.invokeModule('Navigation', 'to', { name: 'x2' }, function () {
    console.log('javascript', 'invokeModule', Array.from(arguments).join(','));
});
console.log('toResult=', toResult);

window.__alita__.invokeModule('UI', 'refresh', { name: 'x2' }, function () {
    console.log('javascript', 'UI.refresh', Array.from(arguments).join(','));
});