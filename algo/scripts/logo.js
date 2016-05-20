(function(){
    window.addEventListener('load', init);

    function init() {
        var logo = document.getElementById("#logo");
        var ctx = logo.getContext('2d');
        ctx.arc(0,0,40,0, Math.PI);
        ctx.fillStyle= '#ffffff';
        ctx.fill();
    }
})()
