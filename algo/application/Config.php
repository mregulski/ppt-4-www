<?php

class Configuration
{
    const AppRoot = 'algo/';
    private static $properties = [
        "application_root" => self::AppRoot,
        "script_path" => self::AppRoot . 'scripts/',
        "style_path" => self::AppRoot . 'styles/',
        "res_path" => self::AppRoot . 'res/',
        "template" => [
            "algorithm" => "application/template/template.html",
            "login" => "application/template/login.html",
            "register" => "application/template/register.html",
            "feedback" => "application/template/feedback.html",
            "blog" => [
                "list" => "application/template/template.html",
                "list_entry" => "application/template/blog/list-entry.html",
                "single_entry" => "application/template/template.html",
                "editor" => "application/template/blog/editor.html",
                "edit" => "application/template/template.html",
                "pagination" => [
                    "container" => "application/template/blog/pagination/pagination.html",
                    "link" => "application/template/blog/pagination/page_link.html",
                ]
            ],
        ],
        "blog" => [
            "entries_per_page" => 6,
            "excerpt_length" => 55,
            "allowed_tags" => '<h1><h2><h3><h4><h5><a><p><br><section><b><i>',
        ],
    ];

    private function __construct()
    {
    }

    public static function property($name)
    {
        $property = explode('.', $name);
        $cur = self::$properties;
        foreach ($property as $prop) {
            $cur = $cur[$prop];
        }
        return $cur;
    }
}



?>
