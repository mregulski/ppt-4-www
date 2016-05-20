var solutions = new Array();

function generateSolutions() {
    var sol = document.getElementById("solutions");
    var n = 8;
    var yPosition = [];
    var counter = 1;

    function hetman(column) {
        for (var i = 0; i < n; i++) {
            if (isFree(column, i)) {
                yPosition[column] = i;
                if (column == n - 1) {
                    solutions.push(yPosition.join(""));
                    counter++;
                    return;
                }
                hetman(column + 1);
            }
        }
    };

    function isFree(x, y) {
        for (var i = 0; i < x; i++) {
            if (y == yPosition[i] || Math.abs(x - i) == Math.abs(y - yPosition[i]))
                return false;
        }
        return true;
    };

    function print() {
        var S = "";
        for (var i = 0; i < solutions.length; i++) {
            S += solutions[i];
            if (i < solutions.length - 1)
                S += ", ";
        }
        sol.innerHTML = S;
    };

    hetman(0);
    print();
    console.log("Solutions generated");
}
// ┌ └ ├ ┬ ┼ │ ┴ ┐ ┘ ┤ ─
function generateDeck() {
    var solution = solutions.shift();
    solutions.push(solution);
    var S = "(" + solution + ")<br>";
    var firstline = " ┌───┬───┬───┬───┬───┬───┬───┬───┐<br>";
    var line = " ├───┼───┼───┼───┼───┼───┼───┼───┤<br>";
    var lastline = " └───┴───┴───┴───┴───┴───┴───┴───┘<br>"
    var numbers = "87654321";

    S += firstline;

    for (var i = 0; i < solution.length; i++) {
        S += numbers[i];
        for (var j = 0; j < 8; j++) {
            if (j == parseInt(solution[i]))
                S += "| H ";
            else
                S += "|   ";
        }
        if (i != solution.length - 1)
            S += "|<br>" + line;
        else
            S += "|<br>" + lastline;
    }

    S += "  A   B   C   D   E   F   G   H"

    console.log("Deck generated");
    return document.getElementById("deck").innerHTML = S;
}

window.addEventListener('load', function() {
    generateSolutions();
    document.getElementById("runButton").onclick = generateDeck;
});
