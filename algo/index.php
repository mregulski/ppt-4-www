<?php
require_once('application/Page.php');
require_once('application/Router.php');
require_once('application/Counter.php');
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
    $page = (new Algorithm\AlgorithmPage(Algorithm\AlgorithmPage::getId($matches[0]), "Algorytmy"))
                -> SetContent(file_get_contents("application/content/".$matches[0].".html"))
                -> RegisterScript('scripts/'.$matches[0].'.js');

    if(file_exists("styles/$matches[0].css")) {
        $page = $page -> RegisterStyle("styles/$matches[0].css");
    }
    echo $page -> Render($counter->getCount());

});

$page = $router->execute($_SERVER['REQUEST_URI']);

?>
