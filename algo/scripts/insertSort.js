var insertionSort;
var callIS;

function insertionSort(t) {
    var tab = [], S = "<span style='font-weight: bold; color: #9cdb4b'>CiÄg przed sortowaniem:</span><br/>";
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
    S += "<br/><br/><span style='font-weight: bold; color: #9cdb4b'>CiÄg po sortowaniu:</span><br/>";
    for (var i = 0; i < t; i++) {
        S += tab[i]+" ";
    }
    return S;
}

function callIS() {
    var n = document.getElementById("varN"), t = Math.abs(parseInt(n.value, 10));
    (isNaN(t)||2>t)&&(t=2), (t>1000000)&&(t=1000000), n.value=t, document.getElementById("window").innerHTML=insertionSort(t)
}
