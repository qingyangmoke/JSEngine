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


function dom() {
    var div = document.createElement('div');
    div.style.width = '750rpx';
    div.style.height = '1400rpx';
    div.style.overflow = 'hidden';
    div.style.alginItems = 'stretch';
    div.style.alginContent = 'stretch';
    div.style.backgroundColor = '#00ff00';
    document.body.appendChild(div);

    var label = document.createElement('label');
    label.setAttribute('text', 'mylabel');
    label.style.width = '375rpx';
    label.style.height = '100rpx';
//    label.flexBasis = 'auto';
//    label.style.flexShrink = 1;
    div.appendChild(label);

    var label = document.createElement('label');
    label.setAttribute('text', 'mylabel2');
    label.style.backgroundColor = '#ff0000';
    label.style.color = '#ffffff';
    label.style.width = '375rpx';
    label.style.height = '100rpx';
    label.style.textAlign = "center";
    label.style.verticalAlign = "middle";
//    label.flexBasis = 'auto';
//    label.style.flexShrink = 1;
    div.appendChild(label);
    
    var img = document.createElement('img');
    img.src = 'http://weathernew.pae.baidu.com/static/weathernew/static/image/0_2c174d7.png';
//    img.style.width = '100%';
//    img.style.height = '100%';
    img.style.height = '375rpx';
    img.flexBasis = 'auto';
//    img.style.flexShrink = 1;
    div.appendChild(img)
    
    var img = document.createElement('img');
    img.src = 'http://weathernew.pae.baidu.com/static/weathernew/static/image/0_2c174d7.png';
//    img.style.width = '100%';
//    img.style.height = '100%';
    img.style.height = '375rpx';
    img.flexBasis = 'auto';
//    img.style.flexShrink = 1;
    div.appendChild(img)
    
    var img = document.createElement('img');
    img.src = 'http://weathernew.pae.baidu.com/static/weathernew/static/image/0_2c174d7.png';
//    img.style.width = '100%';
//    img.style.height = '100%';
    img.style.height = '375rpx';
    img.flexBasis = 'auto';
//    img.style.flexShrink = 1;
    div.appendChild(img)

}

//bootstrap();

dom();
