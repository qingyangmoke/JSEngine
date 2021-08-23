
console.log('Promise', typeof Promise, Promise.toString());

console.log("Promise", typeof Promise.resolve)

Promise.resolve().then(function() {
    console.log('Promise resolve');
});

new Promise(function promise(resolve) {
    console.log('Promise', "init");
    resolve();
}).then(function() {
    console.log('Promise', 'then');
}).catch(function() {
    console.log('Promise', 'catch');
});

setTimeout(function() {
    Promise.sss();
    console.log('setInterval', 'xxxx');
}, 100);

setTimeout(function() {
    console.log('setInterval', 'xxxx');
}, 200)

//window.onerror = function (error) {
//   console.log('__global_onerror_handler__');
//};

window.onerror = function(msg) {
    console.err("error", "xxx");
}