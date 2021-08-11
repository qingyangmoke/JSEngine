const canvas = document.createElement('canvas');
canvas.width = 750;
canvas.height = 750;
var ctx = canvas.getContext('2d');
canvas.setAttribute('width', '750rpx');
canvas.setAttribute('height', '750rpx');
document.body.appendChild(canvas);

const chartData = [
    { x: 0, y: 80 },
    { x: 40, y: 36.55853863365618 },
    { x: 120, y: 16 },
    { x: 200, y: 38.0089784498848 },
    { x: 280, y: 77.10210372001148 },
    { x: 360, y: 78.75412699193723 },
    { x: 440, y: 40.172372570533334 },
    { x: 520, y: 62.98450188146845 },
    { x: 600, y: 39.64461877360302 },
    { x: 640, y: 80 },
];

const tension = 0.2;
for (let i = 0, len = chartData.length - 1; i < len; i++) {
    const p0 = i > 0 ? chartData[i - 1] : chartData[0];
    const p1 = chartData[i];
    const p2 = chartData[i + 1];
    const p3 = chartData[i + 2] || p2;

    p1.cp1x = p1.x + (p2.x - p0.x) * tension;
    p1.cp1y = p1.y + (p2.y - p0.y) * tension;

    p1.cp2x = p2.x - (p3.x - p1.x) * tension;
    p1.cp2y = p2.y - (p3.y - p1.y) * tension;
}

const points = chartData;

ctx.strokeStyle = 'rgba(255, 0, 0, 1)';
ctx.lineWidth = 8;

ctx.save();

ctx.lineCap = 'round';
ctx.beginPath();
ctx.moveTo(points[0].x, points[0].y);
var t = tension != null ? tension : 1;
for (var i = 0; i < points.length - 1; i++) {
    ctx.bezierCurveTo(
        points[i].cp1x,
        points[i].cp1y,
        points[i].cp2x,
        points[i].cp2y,
        points[i + 1].x,
        points[i + 1].y,
    );
}
ctx.stroke();
ctx.closePath();

ctx.beginPath();
ctx.fillStyle = '#ff0000';
ctx.arc(200, 200, 6, 0, 2 * Math.PI);
ctx.fill();
ctx.closePath();

ctx.restore();
canvas.commander.render();

console.log('canvas.commander.render end');
