function fermatTest(q, k)
{
	var a, i, result;

	if (q < 4)
	{
		result = q + " jest pierwsza!";
		return result;
	}

	for (i=0; i < k; i++)
	{
		a = Math.floor((Math.random() * (q-2) + 2));
		if (power_modulo_fast(a, q-1, q) != 1)
		{
			result = "Nie jest pierwsza.";
			return result;
		}
	}
 	result = n + " prawdopodobnie jest pierwsza!";

	return result;
}

function power_modulo_fast(a, b, m)
{
	var i;
	var result = 1;
	var x = a%m;

	for (i=1; i<=b; i<<=1)
	{
		x %= m;

		if ((b&i) != 0)
		{
			result *= x;
			result %= m;
		}

		x *= x;
	}

	return result%m;
}

function callTest()
{
	var e=document.getElementById("varN");
	f=document.getElementById("varK");
	n=Math.abs(parseInt(e.value,10));
	k=Math.abs(parseInt(f.value,10));
	var output = document.getElementById("output");
    output.innerHTML = fermatTest(n, k);
	output.style.display = "block";

}

window.addEventListener('load', function()
{
	document.getElementById("runButton").onclick=callTest;
	window.onresize=checkSize;
});
