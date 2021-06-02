console.log('javascript', 'hello world');

var toResult = window.__module__.invokeModule('Navigation', 'to', { name: 'x2' }, function (errorCode, result) {
    console.log('javascript', 'invokeModule', 'errorCode=', errorCode, 'result=', result);
});
console.log('toResult=', toResult);

window.__module__.invokeModule('UI', 'refresh', { name: 'x2' }, function (errorCode, result) {
    console.log('javascript', 'UI.refresh', 'errorCode=', errorCode, 'result=', result);
});

console.log('toResult=', toResult);