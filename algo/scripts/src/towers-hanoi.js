window.addEventListener('load', function() {
	document.getElementById("ok").onclick = doHanoi;
	document.getElementById("prev").onclick = prev;
	document.getElementById("auto").onclick = doAuto;
	document.getElementById("next").onclick = next;

	document.getElementById("prev").disabled = true;
	document.getElementById("auto").disabled = true;
	document.getElementById("next").disabled = true;


	canvas = document.getElementById("hanoicanvas");
	ctx = canvas.getContext("2d");
	ctx.transform(1, 0, 0, -1, 0, 0); // (╯°□°）╯︵ ┻━┻
	ctx.translate(0, -ctx.canvas.height);
});

// canvas version
var n;
function doHanoi() {
	var input = document.getElementById("input");
	var info = document.getElementById("okInfo");
	n = input.value;
	var el = document.getElementById("canvascont");
	if(isNaN(n) || n<1 || n>8) {
		el.style.display = 'none';
		input.value = "";
		info.innerHTML = "Pick number between 1 and 8.";
	} else {
		el.style.display = 'block';
		A.vals = []; B.vals = []; C.vals = []; steps = []; curr = 0; //clearing variables
		var count = n; count++; count--;
		for (count; count > 0; count--)
			A.vals.push(count); // filling up 1st stack with "disks"
		hanoi(n, "A", "C", "B"); // filling up steps array
		draw();
		document.getElementById("prev").disabled = true;
		document.getElementById("auto").disabled = false;
		document.getElementById("next").disabled = false;
		info.innerHTML = "";
	}
}

function hanoi(n, A, B, C){
	if(n==1) {steps.push([A, B]);}
	else {
		hanoi(n-1, A, C, B);
		steps.push([A, B]);
		hanoi(n-1, C, B, A);
	}
}

var curr;
var steps; //array with steps
var A = {
	pos: { x: 19, y: 3 },
	vals: []
};
var B = {
	pos: { x: 50, y: 3 },
	vals: []
};
var C = {
	pos: { x: 81, y: 3 },
	vals: []
};

function move(A, B) {
	B.vals.push(A.vals.pop());
}
function next() {
	if(curr <= Math.pow(2, n)-2){
		eval("move("+steps[curr][0]+","+steps[curr][1]+")");
		curr++;
		//console.log(A.vals, B.vals, C.vals);
		draw();
		if(curr == Math.pow(2, n)-1){
			document.getElementById("next").disabled = true;
			document.getElementById("auto").disabled = true;
		}
		document.getElementById("prev").disabled = false;

	}
}
function prev() {
	if(curr > 0){
		curr--;
		eval("move("+steps[curr][1]+","+steps[curr][0]+")");
		draw();
		if(curr==0){
			document.getElementById("prev").disabled = true;
		}
		document.getElementById("auto").disabled = false;
		document.getElementById("next").disabled = false;
	}
}
var onauto = false;
function doAuto(){
	var el = document.getElementById("speed");
	var delay = el.value;
	//console.log(delay);
	delay = parseInt(delay);
	//console.log(delay*100);
	if(isNaN(delay) || delay<1 || delay>10) {
		el.value = "";
	} else {
		if(onauto==false) {
			onauto=true;
			auto(next, (11-delay)*100, Math.pow(2, n)-curr);
		} else {
			onauto=false;
		}
	}
}

function auto(action, delay, repetitions) {
    var x = 0;
    var intervalID = window.setInterval(function () {
       if(onauto == false) {window.clearInterval(intervalID); return;}
	   action();
       if (++x === repetitions) {window.clearInterval(intervalID); onauto=false;}
    }, delay);
}

var canvas;
var ctx;

function draw() {
	ctx.clearRect(0, 0, canvas.width, canvas.height); // clearing canvas
	drawPole(A);
	drawPole(B);
	drawPole(C);
}

function drawPole(X) {
	var index;
	var actualH = 0;
	var width;
	var q = Math.pow(4, 1/n);
	ctx.translate(X.pos.x/100*canvas.width, X.pos.y/100*canvas.height);
	ctx.fillStyle = 'gray';
	ctx.fillRect(-1/100*canvas.width, 0, 2/100*canvas.width, 85/100*canvas.height);
	for (index = 0; index < X.vals.length; ++index) {
		width = 6/100*canvas.width * Math.pow(q, X.vals[index]);
		ctx.beginPath();
		ctx.rect(-width/2, actualH, width, canvas.height/10);
		ctx.fillStyle = 'green';
		ctx.fill();
		ctx.lineWidth = 3;
		ctx.strokeStyle = 'black';
		ctx.stroke();

		actualH=actualH+canvas.height/10;
	}
	ctx.translate(-X.pos.x/100*canvas.width, -X.pos.y/100*canvas.height);
}
