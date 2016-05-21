<?php
require_once('application/Page.php');
require_once('application/Router.php');
require_once('application/Counter.php');
require_once('application/Logger.php');

$counter = new Counter();
$counter->update();

$router = new Router();

$router->route('/algo\/$/', function($matches) {
    global $counter;
    echo (new Algorithm\AlgorithmPage(0, "Algorytmy"))
        -> SetContent(file_get_contents("application/content/index.html"))
        -> Render($counter->getCount());
});

$router->route('/[a-zA-Z\-]+$/', function($matches) {
    global $counter;
    Logger::log("\n\troute: " . "'".$_SERVER['REQUEST_URI']."'".
                "\n\tpattern: '/[a-zA-Z\-]+$/'".
                "\n\tmatch: "."'".$matches[0]."'",
                "Router::execute");
    $page = (new Algorithm\AlgorithmPage(Algorithm\AlgorithmPage::getId($matches[0]), "Algorytmy"))
                -> SetContent(file_get_contents("application/content/".$matches[0].".html"));
    if(file_exists("scripts/$matches[0].min.js")) {
        Logger::log("'scripts/".$matches[0].".js'", "Router::execute: Registering script:");
        $page = $page -> RegisterScript('scripts/'.$matches[0].'.min.js');
    }

    if(file_exists("styles/$matches[0].css")) {
        Logger::log("'styles/".$matches[0].".css'", "Router::execute: Registering stylesheet:");
        $page = $page -> RegisterStyle("styles/$matches[0].css");
    }
    
    echo $page -> Render($counter->getCount());

});

$page = $router->execute($_SERVER['REQUEST_URI']);

?>
