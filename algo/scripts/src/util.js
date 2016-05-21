(function(){
    'use strict';
    console.log('util');
    window.addEventListener('load', init);
    window.addEventListener('resize', equalPre);

    function init() {
        MathJax.Hub.Config({
            jax: ["input/TeX", "output/HTML-CSS"],
            displayAlign: "left"
        });
        var menu = document.getElementById("menu");
        document
            .getElementById("menuToggle")
            .addEventListener('click', toggleMenu);
        equalPre();
    }

    // re-enable hidden menu when window is resized above breakpoint
    var mq = window.matchMedia("(min-width: 960px)");
    mq.addListener(enableMenu);

    function enableMenu(mediaQuery) {
        if(mediaQuery.matches) {
            menu.style.display = 'block';
        }
        else {
            menu.style.display = 'none';
        }
    }

    function toggleMenu() {
        if(menu.style.display != 'block')
            menu.style.display = 'block';
        else
            menu.style.display = 'none';
    }

    function equalPre() {
        var preBlocks = document.querySelectorAll('.code pre');
        var maxHeight = 0;
        for(var i = 0; i < preBlocks.length; i++) {
            maxHeight = preBlocks[i].offsetHeight > maxHeight
                    ? preBlocks[i].offsetHeight
                    : maxHeight;
        }

        for(var i = 0; i < preBlocks.length; i++) {
            preBlocks[i].style.height = maxHeight + 'px';
        }

    }

})();
