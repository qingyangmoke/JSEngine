document.title = "scroller 测试";

var scrolller = document.createElement('scroller');
scrolller.style.flex = 1;
scrolller.style.backgroundColor = '#00ff00';
document.body.appendChild(scrolller);

var div = document.createElement('div');
scrolller.appendChild(div);

var label = document.createElement('label');
label.setAttribute('text', 'mylabel');
label.style.width = '375rpx';
label.style.height = '100rpx';
div.appendChild(label);

var label = document.createElement('label');
label.setAttribute('text', 'mylabel2');
label.style.backgroundColor = '#ff0000';
label.style.color = '#ffffff';
label.style.width = '375rpx';
label.style.height = '100rpx';
label.style.textAlign = "center";
label.style.verticalAlign = "middle";
div.appendChild(label);

var input = document.createElement('input');
input.style.placeholderColor = "#ff0000";
input.setAttribute('placeholder', "input hello");
input.setAttribute('type', "number");
div.appendChild(input);

for(let i=0 ; i <50;i ++){
    var img = document.createElement('img');
    img.src = 'http://weathernew.pae.baidu.com/static/weathernew/static/image/0_2c174d7.png';
    img.style.backgroundColor = 'black';
    img.style.width = '375rpx';
    img.style.height = '375rpx';
    div.appendChild(img);
}


setTimeout(function() {
     scrolller.scrollTo(0, 200);
}, 5000);