<?php
require_once('application/Page.php');
require_once('application/Router.php');

$router = new Router();
$router->route('/^.*\/$/', function($uri) {
        echo (new Algorithm\AlgorithmPage(0, "Algorytmy"))
            -> SetContent(file_get_contents('application/content/index.html'))
            -> Render();
    });

$router->route('/^.*\/euclid$/', function($sth) {
    echo (new Algorithm\AlgorithmPage(1, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/euclid.html'))
        -> RegisterScript('scripts/nwd.js')
        -> Render();
});

$router->route('/^.*\/euclid-extended$/', function() {
    echo (new Algorithm\AlgorithmPage(2, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/euclid-extended.html'))
        -> RegisterScript('scripts/euclidExt.js')
        -> Render();
});

$router->route('/^.*\/prime-test$/', function() {
    echo (new Algorithm\AlgorithmPage(3, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/prime-test.html'))
        -> RegisterScript('scripts/primeTest.js')
        -> Render();
});

$router->route('/^.*\/erastotenes-sieve$/', function() {
    echo (new Algorithm\AlgorithmPage(4, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/erastotenes-sieve.html'))
        -> RegisterScript('scripts/sieve.js')
        -> RegisterStyle('styles/sieve.css')
        -> Render();
});

$router->route('/^.*\/insert-sort$/', function() {
    echo (new Algorithm\AlgorithmPage(5, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/insert-sort.html'))
        -> RegisterScript('scripts/insertSort.js')
        -> Render();
});

$router->route('/^.*\/merge-sort$/', function() {
        echo (new Algorithm\AlgorithmPage(6, "Algorytmy"))
            -> SetContent(file_get_contents('application/content/merge-sort.html'))
            -> RegisterScript('scripts/mergeSort.js')
            -> Render();
   });

$router->route('/^.*\/binary-search$/', function() {
    echo (new Algorithm\AlgorithmPage(7, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/binary-search.html'))
        -> RegisterScript('scripts/binarySearch.js')
        -> Render();
});

$router->route('/^.*\/towers-hanoi$/', function() {
    echo (new Algorithm\AlgorithmPage(8, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/towers-hanoi.html'))
        -> RegisterScript('scripts/hanoi.js')
        -> RegisterStyle('styles/hanoi.css')
        -> Render();
});

$router->route('/^.*\/queens-problem$/', function() {
    echo (new Algorithm\AlgorithmPage(9, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/queens-problem.html'))
        -> RegisterScript('scripts/queens.js')
        -> Render();
});

$router->route('/^.*\/knights-tour$/', function() {
    echo (new Algorithm\AlgorithmPage(10, "Algorytmy"))
        -> SetContent(file_get_contents('application/content/knights-tour.html'))
        -> RegisterScript('scripts/knight.js')
        -> Render();
});

$page = $router->execute($_SERVER['REQUEST_URI']);

?>
