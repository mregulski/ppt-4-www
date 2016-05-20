var insertionSort;
var callIS;
window.addEventListener('load', function() {
	document.getElementById('runButton').addEventListener('click', callIS);
});
function insertionSort(t) {
    var tab = [], S = "<span>Ciąg przed sortowaniem:</span><br/>";
    for (var i = 0; i < t; i++) {
        tab[i] = Math.floor((Math.random()*100)+1);
        S += tab[i]+" "
    }
    for (var i = 1; i < tab.length; i++) {
        var tmp = tab[i];
        var j = i-1;
        while ((j >= 0) && (tab[j] > tmp)) {
            tab[j+1] = tab[j];
            j--;
        }
        tab[j+1] = tmp;
    }
    S += "<br/><br/><span>Ciąg po sortowaniu:</span><br/>";
    for (var i = 0; i < t; i++) {
        S += tab[i]+" ";
    }
    return S;
}

function callIS() {
    var n = document.getElementById("varN"), t = Math.abs(parseInt(n.value, 10));
    (isNaN(t)||2>t)&&(t=2), (t>1000000)&&(t=1000000), n.value=t, document.getElementById("output").innerHTML=insertionSort(t);
    document.getElementById("output").style.display = "block";
}
