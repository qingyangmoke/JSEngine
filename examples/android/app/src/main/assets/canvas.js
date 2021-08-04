
console.log('javascript', 'hello world');

var canvas = document.createElement('canvas');
canvas.setAttribute("width", 1080);
canvas.setAttribute("height", 800);

var context = canvas.getContext('2d');
context.lineWidth = 4;
context.strokeStyle = 'rgba(0,255,0,1)';
context.beginPath();
context.moveTo(0, 0);
context.lineTo(200, 200);
context.lineTo(300, 10);
context.lineTo(400, 200);
context.stroke();

context.strokeStyle = 'rgba(255, 0, 0, 1)';
context.lineWidth = 2;
context.beginPath();
context.moveTo(50, 50);
context.lineTo(250, 250);
context.lineTo(350, 60);
context.lineTo(450, 250);
context.stroke();

canvas.commander.render();