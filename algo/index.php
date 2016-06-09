<?php
require_once('application/AlgorithmPage.php');
require_once('application/Router.php');
require_once('application/Counter.php');
require_once('application/Logger.php');
require_once('application/Blog/Session.php');
require_once('application/Blog/LoginPage.php');
require_once('application/Blog/Blog.php');
require_once('application/Config.php');
use Session\Session;
use Blog\LoginPage;
use Blog\BlogPage;

$counter = new Counter();
$router = new Router();

$application_root = addcslashes(Configuration::property('application_root'), '/');

/**
 * Application root
 */
$router->route('/' . $application_root . '($|\/$)/', function ($matches) {
    global $counter;
    $counter->update();
    Logger::log("Rendering root", "Router::execute(/)");
    echo (new Algorithm\AlgorithmPage(0, "Algorytmy"))
        -> SetContent(file_get_contents("application/content/index.html"))
        -> Render($counter->getCount());
});

/**
 * Login page
 */
$router->route('/' . $application_root . 'login($|\/$)/', function ($matches) {
    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        echo (new LoginPage('login'))->render(null, null);
    } else {
        if (Session::login()) {
            Logger::log("user logged in: " . $_SESSION['user'], "Router::execute(/login");
            header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
        } else {
            http_response_code(403);
            echo (new LoginPage('login'))->render("Nieprawidłowe dane", 'error');
        }
    }
});
/**
 * Registration
 */
$router->route('/' . $application_root . 'register($|\/$)/', function ($matches) {
    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        echo (new LoginPage('register'))->render(null, null);
        return;
    }
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        if ((new \Db\Database())->create_user($_POST['username'], $_POST['password'])) {
            echo (new LoginPage('login'))->render("Utworzono nowe konto", 'success');
        }
    } else {
        if (Session::login()) {
            Logger::log("user logged in: " . $_SESSION['user'], "Router::execute(/login");
            header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
        } else {
            http_response_code(403);
            echo (new LoginPage('register'))->render("Nieprawidłowe dane", 'error');
        }
    }
});

/**
 * Logout
 */
$router->route('/' . $application_root . 'logout($|\/$)/', function () {
    Session::logout();
    header('Location: /' . Configuration::property('application_root'));
    return;
});


/**
 * Blog front page
 */
$router->route('/' . $application_root . 'blog($|\/$)/', function ($matches) {
    global $counter;
    $counter->update();
    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
        echo (new BlogPage(false, 1, null))->render($counter->getCount());
    } else {
        echo 'posted';
    }
});

/**
 * Further blog pages
 */
$router->route('/' . $application_root . 'blog\/([0-9]+)($|\/$)/', function ($matches) {
    global $counter;
    $counter->update();
    $page_number = (int)$matches[1];
    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
        if ($page_number <= (new \Db\Database())->get_page_count()) {
            echo (new BlogPage(false, $page_number, null))->render($counter->getCount());
            return;
        }
        http_response_code(404);
        echo("<html><body><h1>404 - not found</h1><p>Requested URL has not been found.</p></body></html>");
    }
});

/**
 * New blog post.
 * GET: editor page
 * POST: add entry
 */
$router->route('/' . $application_root . 'blog\/new($|\/$)/', function ($matches) {
    global $counter;
    if (!Session::check()) {
        header("Location: /" . Configuration::property('application_root') . 'login');
        return;
    }
    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
        echo (new BlogPage(true, null, null))->render($counter->getCount());
    } else if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        if ((new \Db\Database())->save_entry($_POST)) {
            http_response_code(303);
            header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
            return;
        } else {
            http_response_code(500);
            header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
            return;
        }
    }
});

/**
 * GET: editor page
 */
$router->route('/' . $application_root . 'blog\/entry\/([0-9]+)\/edit($|\/$)/', function ($matches) {
    global $counter;
    $post_number = $matches[1];
    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
        echo (new BlogPage(true, null, $post_number))->render($counter->getCount());
        return;
    } else {
        http_response_code(406);
    }
});

/**
 * Particular blog entry
 * GET: entry
 * POST/patch: update
 * POST/delete: delete
 */
$router->route('/' . $application_root . 'blog\/entry\/([0-9]+)($|\/$)/', function ($matches) {
    global $counter;
    $post_number = $matches[1];

    if ($_SERVER['REQUEST_METHOD'] == 'GET') {
        Logger::log("Entry: #$post_number", "Router::execute(/blog/entry/{id})");
        echo (new BlogPage(false, null, $post_number))->render($counter->getCount());
        return;
    }
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
        if ($_POST['method'] == 'PATCH') { // update
            if ((new \Db\Database())->update_entry($post_number, $_POST)) {
                http_response_code(302);
                header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog/entry/$post_number");
                return;
            }
            http_response_code(500);
            header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
            return;

        } else if ($_POST['method'] == 'DELETE') {
            if ((new \Db\Database())->delete_entry($post_number)) {
                http_response_code(200);
                header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
                return;
            }
            http_response_code(500);
            header("Location: https://" . $_SERVER['HTTP_HOST'] . "/algo/blog");
            return;
        }
    }

});

/**
 * Autowired algorithm pages
 */
$router->route('/' . $application_root . '([a-zA-Z\-]+)$/', function ($matches) {
    global $counter;
    Logger::log("\n\troute: " . "'".$_SERVER['REQUEST_URI']."'".
                "\n\tpattern: '/[a-zA-Z\-]+$/'".
        "\n\tmatch: " . "'" . $matches[1] . "'",
                "Router::execute");
    $page = (new Algorithm\AlgorithmPage(Algorithm\AlgorithmPage::getId($matches[1]), "Algorytmy"))
        ->SetContent(file_get_contents("application/content/" . $matches[1] . ".html"));
    if (file_exists("scripts/$matches[1].min.js")) {
        Logger::log("Registering script: 'scripts/" . $matches[1] . ".js'", "Router::execute");
        $page = $page->register_script('scripts/' . $matches[0] . '.min.js');
    }

    if (file_exists("styles/$matches[1].css")) {
        Logger::log("Registering stylesheet: 'styles/" . $matches[1] . ".css'", "Router::execute");
        $page = $page->register_style("styles/$matches[1].css");
    }
    
    echo $page -> Render($counter->getCount());

});

Logger::log('uri: ' . $_SERVER['REQUEST_URI'], '');
$page = $router->execute($_SERVER['REQUEST_URI']);
?>
