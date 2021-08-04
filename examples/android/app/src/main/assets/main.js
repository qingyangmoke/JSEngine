console.log('javascript', 'hello world');


var toResult = window.__module__.invokeModule('Navigation', 'to', { name: 'x2' }, function (errorCode, result) {
    console.log('javascript', 'invokeModule', 'errorCode=', errorCode, 'result=', result);
});
console.log('toResult=', toResult);

window['JSTimers'] = {
    sayHi: function(args) {
        console.log("JSTimers.sayHi", args);
    }
};

window.setTimeout(function() {
  console.log('setTimeout callback');
}, 1000);

var handle = window.setInterval(function() {
  console.log('setInterval callback');
}, 1000);

window.setTimeout(function() {
    console.log('setTimeout callback2');
  window.clearInterval(handle);
}, 5000);

//
//window.__module__.invokeModule('UI', 'refresh', { name: 'x2' }, function (errorCode, result) {
//    console.log('javascript', 'UI.refresh', 'errorCode=', errorCode, 'result=', result);
//});
//
//console.log('toResult=', toResult);