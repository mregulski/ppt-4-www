window.addEventListener('load', function() {
	document.getElementById('runButton').addEventListener('click', callNWD);

});

function callNWD() {
	var e=document.getElementById("varX"), n=document.getElementById("varY"), t=Math.abs(parseInt(e.value,10)), a=Math.abs(parseInt(n.value,10));
	(isNaN(t)||1>t)&&(t=1), (isNaN(a)||1>a)&&(a=1), e.value=t, n.value=a, document.getElementById("output").innerHTML=nwd(t, a)
	document.getElementById('output').style.display = "block";
}

function nwd(a,b) {
	var S;
	var c;
	S = "";
	while (b != 0){
		S = S + "(" + a + "," + b + ") &#8594; \n"
		c = a;
		a = b;
		b = c % b;
	}
	S = S + a;
	return S;
}
