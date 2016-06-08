<?php

class Configuration
{
    const AppRoot = 'algo/';
    private static $config;
    private static $properties = [
        "application_root" => self::AppRoot,
        "script_path" => self::AppRoot . 'scripts/',
        "style_path" => self::AppRoot . 'styles/',
        "res_path" => self::AppRoot . 'res/',
        "template" => [
            "algorithm" => "application/template/template.html",
            "login" => "application/template/login.html",
            "feedback" => "application/template/feedback.html",
            "blog" => "application/template/template.html",
            "blog_entry" => "application/template/blog-entry.html",
            "blog_editor" => "application/template/blog-editor.html",
            "editor" => "application/template/template.html",
        ],
        "blog" => [
            "entries_per_page" => 10,
        ],
    ];

    private function __construct()
    {
    }

    public static function property($name)
    {
        $property = explode('.', $name);
        if (count($property) == 1) {

            return self::$properties[$property[0]];
        }
        if (count($property) == 2) {
            return self::$properties[$property[0]][$property[1]];
        }
    }
}



?>
