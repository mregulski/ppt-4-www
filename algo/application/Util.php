<?php
require_once('application/Logger.php');

/**
 * Created by PhpStorm.
 * User: mrmar
 * Date: 09.06.2016
 * Time: 13:42
 */
class Util
{
    static function get_excerpt($sentence)
    {
        $count = Configuration::property("blog.excerpt_length");
        preg_match("/(?:(\w|<|>)+(?:\W+|$)){0,$count}/", $sentence, $matches);
        Logger::log("Excerpt for:\n$sentence\nis\n$matches[0]", "Util.get_excerpt");
        return $matches[0];
    }
}