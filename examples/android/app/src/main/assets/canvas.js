
console.log('javascript', 'hello world');

var img = document.createElement('img');
img.style.width = '375rpx';
img.style.height = '375rpx';

function preLoad(callback) {
    img.onload = callback;
    img.src = 'http://weathernew.pae.baidu.com/static/weathernew/static/image/0_2c174d7.png';
}

var canvas = document.createElement('canvas');
var context = canvas.getContext('2d');
//canvas.setAttribute("width", "750rpx");
//canvas.setAttribute("height", "750rpx");
canvas.width = 750;
canvas.height = 750;
document.body.appendChild(canvas);

function draw() {
    context.lineWidth = 8;
    context.strokeStyle = 'rgba(0,255,0,1)';
    context.beginPath();
    context.moveTo(0, 0);
    context.lineTo(200, 200);
    context.lineTo(300, 10);
    context.lineTo(400, 200);
    context.stroke();

    context.strokeStyle = 'rgba(255, 0, 0, 1)';
    context.lineWidth = 1;
    context.beginPath();
    context.moveTo(50, 50);
    context.lineTo(250, 250);
    context.lineTo(350, 60);
    context.lineTo(450, 250);
    context.stroke();

    context.beginPath();
    context.moveTo(50,20);
    context.bezierCurveTo(230, 30, 150, 60, 50, 100);
    context.stroke();

    context.beginPath();
    context.strokeStyle = 'rgba(0, 0, 255, 1)';
    context.lineWidth = 4;
    context.strokeRect(100,100, 200, 100);

    context.fillStyle = 'rgba(0, 0, 255, 1)';

    context.beginPath();
    context.fillRect(100, 300, 200, 100);
    context.drawImage(img, 300, 0);

    context.beginPath();
    context.rect(100, 500, 200, 100);
    context.stroke();


    context.fillStyle = 'rgba(0, 255, 0, 1)';
    context.beginPath();
    context.rect(300, 500, 200, 100);
    context.fill();

    context.beginPath();
    context.arc(300, 300, 200, Math.PI / 4 * -1, -Math.PI / 2, false);
    context.stroke();

    canvas.commander.render();
}

//draw();
//preLoad(draw);
context.strokeStyle = "rgba(0, 0, 255, 1)";
context.lineWidth = 2;
context.save();
context.strokeStyle = "rgba(255, 0, 255, 1)";
context.lineWidth = 4;
context.rotate(Math.PI / 4);
context.beginPath();
context.moveTo(0, 300);
context.lineTo(750, 300);
context.stroke();
context.restore();

context.beginPath();
context.arc(300, 300, 200, -(Math.PI / 4), Math.PI * 1 / 4, true);
context.stroke();

//context.save();
//context.translate(100, 0);
//context.strokeStyle = "rgba(255, 0, 0, 1)";
//context.beginPath();
//context.arc(300, 300, 200, -(Math.PI / 4), Math.PI * 1 / 4, true);
//context.stroke();
//context.restore();

context.save();
context.lineWidth = 2;
context.scale(0.5, 0.5);
context.translate(150, 150);
context.strokeStyle = "rgba(255, 0, 0, 1)";
context.beginPath();
context.arc(300, 300, 200, -(Math.PI / 4), Math.PI * 1 / 4, true);
context.stroke();
context.restore();

context.strokeStyle = "rgba(0, 255, 0, 1)";
context.beginPath();
context.arc(310, 300, 200, -(Math.PI / 4), Math.PI * 1 / 4, true);
context.stroke();

canvas.commander.render();

console.log("canvas width=", canvas.getAttribute("width"), canvas.getAttribute("height"));

setTimeout(function() {
  canvas.width = 600;
  console.log('setTimeout callback', '500');
}, 5000);

canvas.addEventListener("surfaceChanged", function() {
    console.log('js surfaceChanged callback', '500');
    draw();
});