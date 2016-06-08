<?php
class Router {
    private $routes = array();

    public function route($pattern, $callback) {
//        Logger::log("Registering route: " . $pattern, 'Router::route');
        $this->routes[$pattern] = $callback;
    }

    public function execute($uri) {
//        Logger::log('resolving uri: ' . $uri, 'Router::execute');
        foreach($this->routes as $pattern => $callback) {
            if(preg_match($pattern, $uri, $params) === 1) {
                return call_user_func($callback, $params);
            }
        }
    }
}
?>
