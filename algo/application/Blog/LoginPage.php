<?php
namespace Blog;
require_once('application/Page.php');
/**
 * Created by PhpStorm.
 * User: mrmar
 * Date: 08.06.2016
 * Time: 14:23
 */

use Logger;

class LoginPage extends \Page
{
    private $template;
    private $mode;

    public function __construct($mode)
    {
        if ($mode === 'login' || $mode === 'register') {
            $this->mode = $mode;
        } else {
            throw new \Exception("invalid mode for LoginPage");
        }
        $this->template = $this->get_template($mode);
        Logger::log('template:' . $this->template);
    }

    public function render($msg, $type)
    {
        return str_replace(['{{msg}}', '{{msg_class}}', '{{action}}', '{{title}}'],
            [$msg, $type, $this->mode, $this->mode == 'login' ? "Logowanie do bloga" : "Nowe konto"],
            $this->template);
    }

    public function authorize($username, $password)
    {

    }
}