(function(){
    'use strict';
    console.log('util');
    window.addEventListener('load', init);

    function init() {
        MathJax.Hub.Config({
            jax: ["input/TeX", "output/HTML-CSS"],
            displayAlign: "left"
        });
        menu = document.getElementById("menu");
        document
            .getElementById("menuToggle")
            .addEventListener('click', toggleMenu);
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

})();