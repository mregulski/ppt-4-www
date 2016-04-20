page = (function(){
    'use strict';
    var menu = null;
    var input = null;
    var run = null;
    window.onload = function() {
        menu = document.getElementById("menu");
        input = document.getElementById("array");
        run = document.getElementById("runButton");

        document.getElementById("menuToggle").onclick = toggleMenu;
        run.addEventListener('click', runSort);
        input.addEventListener('keypress', checkInput);
    }

    // re-enable hidden menu when window is resized above breakpoint
    var mq = window.matchMedia("(min-width: 680px)");
    mq.addListener(enableMenu);


    function checkInput() {
        var array = input.value.split(/[,; ]/);
        //console.log(array);
        if(array.length > 1) {
            run.disabled = false;
        }
        else {
            run.disabled = true;
        }
    }

    function enableMenu(mediaQuery) {
        if(mediaQuery.matches) {
            menu.style.display = 'block';
        }
    }

    function runSort() {
        var array = input.value.split(/[,; ]/);
        console.log(array);
        array = array.map(function(x) {
            return parseInt(x,10);
        })
        console.log(sort.mergeSort(array));
    }

    function toggleMenu() {
        if(menu.style.display != 'block')
            menu.style.display = 'block';
        else
            menu.style.display = 'none';
    }

})();
