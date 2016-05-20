<?php
/*
https://github.com/moagrius/RegexRouter
*/
class Router {
    private $routes = array();

    public function route($pattern, $callback) {
        $this->routes[$pattern] = $callback;
    }

    public function execute($uri) {
        foreach($this->routes as $pattern => $callback) {
            if(preg_match($pattern, $uri, $params) === 1) {
                return call_user_func($callback, $params);
            }
        }
    }
}
?>
