
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

//setInterval(function() {
//    console.log('setInterval', 'xxxx');
//}, 100)

// Global error handler used by JS Engine
// // @ts-ignore
window.__global_onerror_handler__ = function (error) {
   console.log('__global_onerror_handler__');
};