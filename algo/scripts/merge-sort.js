(function() {
    'use strict';
    var input, output, run;
    window.addEventListener('load', init);

    // return {
    //     mergeSort: mergeSort
    // };

    function init() {
        input = document.getElementById("array");
        run = document.getElementById("runButton");

        run.addEventListener('click', runSort);
        input.addEventListener('keyup', checkInput);
    }

    function mergeSort(array) {
        if(output === undefined) {
            output = document.getElementById("output");
            output.style.display = 'block';
        }
        output.innerHTML = "";
        return _mergeSort(array, 0);
    }

    function _mergeSort(array, level) {


        if (array.length <= 1) {
            return array;
        }

        var left = [];
        var right = [];
        for (var i = 0; i < array.length; i++) {
            if(i%2 == 0) {
                left.push(array[i]);
            }
            else {
                right.push(array[i]);
            }
        }
        log("split " + array, level);
        log("->  left: " + left, level);
        log("-> right: " + right, level);

        // console.log("split:")
        // console.log("\tleft: " + left);
        // console.log("\tright: " + right);
        left = _mergeSort(left, level+1);
        right = _mergeSort(right, level+1);
        return merge(left, right, level);
    }

    function merge(left, right, level) {
        // var output = document.getElementById("output");
        var result = [];
        log("merging", level);
        log("    left: " + left, level);
        log(" & right: " + right, level);

        // console.log("merge:")
        // console.log("    left: " + left);
        // console.log("  &right: " + right);
        while (left.length > 0 && right.length > 0) {
            if(left[0] <= right[0]) {
                result.push(left.shift());
            }
            else {
                result.push(right.shift());
            }

        }
        while (left.length > 0) {
            result.push(left.shift());
        }

        while (right.length > 0) {
            result.push(right.shift());
        }
        log("    -> result: " + result,level);
        // console.log("\tresult: " + result);
        return result;
    }

    function log(text, level) {
        var br = document.createElement("br");
        // var ell = '<div class="col-6-6 level-"' + level + '>' + text + '</div>';

        var el = document.createElement("span");
        // el.setAttribute("level", level);
        el.classList.add("level-"+level%10);
        el.classList.add("col-6-6");
        var txt = document.createTextNode("--- ".repeat(level) + text);
        //
        el.appendChild(txt);
        output.appendChild(el);
        output.appendChild(br);
        // output.innerHTML += ell;
    }

    function checkInput() {
        var array = getSortableData(input);
        console.log(array);
        if(array.length > 1) {
            run.disabled = false;
        }
        else {
            run.disabled = true;
        }
    }

    function runSort() {
        var array = getSortableData(input);
        console.log(parseInt(array[0]) != NaN);
        if(!isNaN(parseInt(array[0]))) {
            array = array.map(function(x) {
                return parseInt(x,10);
            });
        }
        console.log(mergeSort(array));
    }

    function getSortableData(input) {
        return input.value.split(/[\s;,]+/);
    }

})();
