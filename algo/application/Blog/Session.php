<?php
namespace Session;
require_once('application/Db/Database.php');
use Db\Database;

function isSecure()
{
    return (!empty($_SERVER[`HTTPS`]) && $_SERVER[`HTTPS`] !== 'off') || $_SERVER['SERVER_PORT'] == 443;
}

class Session
{

    static function check()
    {
        if (session_status() != PHP_SESSION_ACTIVE) {
            session_start();
        }
        return isSecure() && isset($_SESSION['user']);

    }


    static function login()
    {
        if (!isSecure()) {
            return false;
        }
        $username = $_POST['username'];
        $password = $_POST['password'];
        $db = new Database();

        $user = $db->get_user($username);
        if ($user) {
            if (hash('sha256', $password) === $user['hash']) {
                self::create($user);
                return true;
            }
        }
        return false;
    }

    static function create($user)
    {
        $time = 60 * 60;
        $path = "/algo/";
        $domain = $_SERVER['SERVER_ADDR'];
        $secure = true;
        $http = true;
        session_set_cookie_params($time, $path, $domain, $secure, $http);
        session_start();
        $_SESSION['user'] = $user['username'];
        foreach ($_SESSION as $x => $y) {
            \Logger::log("session." . $x . " = " . $y, '[Session.create]');
        }
    }

    static function logout()
    {
        session_start();
        $old_cookie = session_get_cookie_params();
        session_unset();
        session_destroy();
        setcookie(session_name(), '', 1, $old_cookie['path'], $old_cookie['domain'], $old_cookie['secure'], $old_cookie['httponly']);
    }
}

?>