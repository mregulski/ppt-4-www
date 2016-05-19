var wynik;
function rozszerzonyAe(a,b){
    var x,y,xLast,yLast, q,e,m,as=a,bs=b;

    x = 1;
    y = 0;
    xLast = 0, yLast = 1;
    while(a != 0) {
        q = b / a;
        r = b % a;
        m = xLast - Math.floor(q) * x;
        n = yLast - Math.floor(q) * y;
        xLast = x, yLast = y;
        x = m, y = n;
        b = a, a = r;
    }
    wynik = wynik +" ="+xLast+"*"+as+" + "+yLast+"*"+bs+" = "+(xLast*as+yLast*bs)+"\n";
}
function call(a,b){
    wynik = "EEA("+a+","+b+")";
    rozszerzonyAe(a,b);
    return wynik;
}



function callRAE(){
    var e=document.getElementById("varX"),
    n=document.getElementById("varY"),
    t=Math.abs(parseInt(e.value,10)),
    a=Math.abs(parseInt(n.value,10));
    (isNaN(t)||1>t)&&(t=1),(isNaN(a)||1>a)&&(a=1),
    e.value=t,n.value=a,
    document.getElementById("trace").innerHTML=call(t,a)
}
