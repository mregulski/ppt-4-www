<?php

/**
 * Created by PhpStorm.
 * User: mrmar
 * Date: 08.06.2016
 * Time: 19:37
 */
class Page
{
    protected $scripts = [];
    protected $styles = [];

    function register_script($script)
    {
        $this->scripts[] = $script;
        return $this;
    }

    function register_style($style)
    {
        $this->styles[] = $style;
        return $this;
    }

    protected function ScriptBlock()
    {
        $scriptTags = "";
        foreach($this->scripts as $script) {
            $scriptTags .= "<script src='{$script}'></script>\n";
        }
        unset($script);
        return $scriptTags;
    }

    protected function StyleBlock()
    {
        $styleTags = "";
        foreach($this->styles as $style) {
            $styleTags .= "<link rel='stylesheet' href='$style'/>\n";
        }
        unset($style);
        return $styleTags;
    }

    protected function link($href)
    {
        return '/' . \Configuration::property('application_root') . "$href";
    }


}