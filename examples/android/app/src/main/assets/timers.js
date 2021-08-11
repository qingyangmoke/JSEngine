window['JSTimers'] = {
    sayHi: function(args) {
        console.log("JSTimers.sayHi", args);
    }
};

window.setTimeout(function() {
  console.log('setTimeout callback', '100');
}, 1000);


var handle = window.setInterval(function() {
  console.log('setInterval callback');
}, 1000);

window.setTimeout(function() {
  clearInterval(handle);
  console.log('setTimeout callback', '500');
}, 5000);
