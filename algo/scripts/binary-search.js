function binarySearch(array, key) {
    var lo = 0,
        hi = array.length - 1,
        mid,
        element,
		str,
		first = 1;
    while (lo <= hi) {
        mid = Math.floor((lo + hi) / 2, 10);
        element = array[mid];
		if(first != 1) str = str + " -> " + element;
		else{
			str = element;
			first = 0;
		}

        if (element < key) {
            lo = mid + 1;
        } else if (element > key) {
            hi = mid - 1;
        } else {
            return str;
        }
    }
	str = "Błędna liczba";
    return str;
}

function callBS(){
	var e=document.getElementById("varX"),
	t=Math.abs(parseInt(e.value,10));
    var output = document.getElementById("output");
	output.innerHTML = binarySearch([1,2,3,4,5,6,7,8,9,10], t)
    output.style.display = "block";
}


/*
 * Wstawienie akcji do przyciskow
 */

 window.addEventListener('load', function() {
	document.getElementById("runButton").onclick=callBS;
});
