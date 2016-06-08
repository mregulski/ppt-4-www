<?php
/**
 * Created by PhpStorm.
 * User: mrmar
 * Date: 08.06.2016
 * Time: 14:23
 */

namespace Blog;

use Logger;

class LoginPage
{
    private $template;
    private $config;

    public function __construct()
    {
        $this->template = \Configuration::property('template.login');
        Logger::log('template:' . $this->template);
    }

    public function render($error)
    {
        return str_replace('{{ERROR_MSG}}', $error, file_get_contents($this->template));
    }

    public function authorize($username, $password)
    {

    }
}