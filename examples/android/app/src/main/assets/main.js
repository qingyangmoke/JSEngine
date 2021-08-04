console.log('javascript', 'hello world');

window['JSTimers'] = {
    sayHi: function(args) {
        console.log("JSTimers.sayHi", args);
    }
};

//window.__module__.setTimeout(function() {
//  console.log('timer');
//}, 1000)

//var toResult = window.__module__.invokeModule('Navigation', 'to', { name: 'x2' }, function (errorCode, result) {
//    console.log('javascript', 'invokeModule', 'errorCode=', errorCode, 'result=', result);
//});
//console.log('toResult=', toResult);
//
//window.__module__.invokeModule('UI', 'refresh', { name: 'x2' }, function (errorCode, result) {
//    console.log('javascript', 'UI.refresh', 'errorCode=', errorCode, 'result=', result);
//});
//
//console.log('toResult=', toResult);