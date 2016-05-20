<?php
require_once('application/Page.php');
require_once('application/Router.php');
require_once('application/Counter.php');
$counter = new Counter();
$counter->update();
// $counter->getCount() = $counter->getCount();

$router = new Router();

$router->route('/algo\/$/', function($matches) {
    global $counter;
    echo (new Algorithm\AlgorithmPage(0, "Algorytmy"))
        -> SetContent(file_get_contents("application/content/index.html"))
        -> Render($counter->getCount());
});

$router->route('/[a-zA-Z\-]+$/', function($matches) {
    global $counter;
    echo (new Algorithm\AlgorithmPage(Algorithm\AlgorithmPage::getId($matches[0]), "Algorytmy"))
        -> SetContent(file_get_contents("application/content/".$matches[0].".html"))
        -> RegisterScript('scripts/'.$matches[0].'.js')
        -> Render($counter->getCount());
});



// $router->route('/^.*\/$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(0, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/index.html'))
//         -> Render($counter->getCount());
//     });
//
// $router->route('/^.*\/euclid$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(1, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/euclid.html'))
//         -> RegisterScript('scripts/nwd.js')
//         -> Render($counter->getCount());
// });
//
// $router->route('/^.*\/euclid-extended$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(2, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/euclid-extended.html'))
//         -> RegisterScript('scripts/euclidExt.js')
//         -> Render($counter->getCount());
// });
//
// $router->route('/^.*\/prime-test$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(3, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/prime-test.html'))
//         -> RegisterScript('scripts/primeTest.js')
//         -> Render($counter->getCount());
// });
//
// $router->route('/^.*\/erastotenes-sieve$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(4, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/erastotenes-sieve.html'))
//         -> RegisterScript('scripts/sieve.js')
//         -> RegisterStyle('styles/sieve.css')
//         -> Render($counter->getCount());
// });
//
// $router->route('/insert-sort$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(5, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/insert-sort.html'))
//         -> RegisterScript('scripts/insertSort.js')
//         -> Render($counter->getCount());
// });
//
// $router->route('/merge-sort$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(6, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/merge-sort.html'))
//         -> RegisterScript('scripts/mergeSort.js')
//         -> Render($counter->getCount());
//    });
//
// $router->route('/binary-search$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(7, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/binary-search.html'))
//         -> RegisterScript('scripts/binarySearch.js')
//         -> Render($counter->getCount());
// });
//
// $router->route('/towers-hanoi$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(8, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/towers-hanoi.html'))
//         -> RegisterScript('scripts/hanoi.js')
//         -> RegisterStyle('styles/hanoi.css')
//         -> Render($counter->getCount());
// });
//
// $router->route('/queens-problem$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(9, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/queens-problem.html'))
//         -> RegisterScript('scripts/queens.js')
//         -> Render($counter->getCount());
// });
//
// $router->route('/knights-tour$/', function() {
//     global $counter;
//     echo (new Algorithm\AlgorithmPage(10, "Algorytmy"))
//         -> SetContent(file_get_contents('application/content/knights-tour.html'))
//         -> RegisterScript('scripts/knight.js')
//         -> Render($counter->getCount());
// });

// echo $_SERVER['REQUEST_URI'];
$page = $router->execute($_SERVER['REQUEST_URI']);

?>
