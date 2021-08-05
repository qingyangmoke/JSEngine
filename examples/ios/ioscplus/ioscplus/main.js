function bootstrap() {
    //    console.log('bootstrap', Date.now());
    //    var a = 1;
    //    window.delayCall(function() {
    //        console.log('callback', Array.from(arguments).join(','));
    //    }, 2000);
    //
    var result = window.__module__.invokeModule('Navigation', 'to', { name: 'xxxx' }, function () {
        console.log('invokeModule', Array.from(arguments).join(','));
    });

    console.log('Navigation.to result=', result);

    // var div = document.createElement('div');
    // div.style = {"xxx": 1};
    // div.style.abc = "xxx";
    // console.log("userAgent=", typeof window.navigator);

    // 定义一个js module
    window['JSTimers'] = {
        sayHi: function (args) {
            console.log('JSTimers.sayHi', args);
        },
    };
    
    var time = Date.now();
   
    window.setTimeout(function() {
      console.log('setTimeout callback', '100', Date.now() - time);
    }, 1000);

    var handle = window.setInterval(function() {
      console.log('setInterval callback', Date.now() - time);
    }, 1000);

    window.setTimeout(function() {
      clearInterval(handle);
      console.log('setTimeout callback', '500', Date.now() - time);
    }, 5000);
}

bootstrap();
