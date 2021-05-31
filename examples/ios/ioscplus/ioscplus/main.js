function bootstrap() {
    console.log('bootstrap', Date.now());
    var a = 1;
    window.delayCall(function() {
        console.log('callback', Array.from(arguments).join(','));
    }, 2000);
    
    var result = window.__alita__.invokeModule('Navigation', 'to', { name:'xxxx' }, function() {
        console.log('invokeModule', Array.from(arguments).join(','));
    });
    
    console.log("Navigation.to.result=", result);
}

bootstrap();
