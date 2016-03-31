sort = (function() {
    var output = undefined;
    return {
        mergeSort: mergeSort
    };

    function mergeSort(array) {
        if(output === undefined) {
            output = document.getElementById("output");
        }
        while(output.firstChild) {
            output.removeChild(output.firstChild);
        }
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
        log("split " + array, "split", level);
        log("->  left: " + left, "split", level);
        log("-> right: " + right, "split", level);

        console.log("split:")
        console.log("\tleft: " + left);
        console.log("\tright: " + right);
        left = _mergeSort(left, level+1);
        right = _mergeSort(right, level+1);
        return merge(left, right, level);
    }

    function merge(left, right, level) {
        var output = document.getElementById("output");
        var result = [];
        log("merging","merge", level);
        log("    left: " + left, "merge", level);
        log(" & right: " + right, "merge", level);

        console.log("merge:")
        console.log("    left: " + left);
        console.log("  &right: " + right);
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
        log("    -> result: " + result, "merge", level);
        console.log("\tresult: " + result);
        return result;
    }

    function log(text, step, level) {
        var br = document.createElement("br");
        var el = document.createElement("span");
        el.classList.add("level-"+level)
        if(step == "split")
        {
            var txt = document.createTextNode('-'.repeat(2*level)+text);

        }
        else if (step == "merge") {
            var txt = document.createTextNode('-'.repeat(2*(level)) + text);
        }
        else {
            return;
        }
        el.appendChild(txt);
        output.appendChild(el);
        output.appendChild(br);
    }

})();
