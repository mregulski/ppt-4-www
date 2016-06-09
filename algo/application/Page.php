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

    protected function get_template($name)
    {
        $template_file = Configuration::property('template.' . $name);
        Logger::log("Template '$name' resolved to '$template_file'.", "Page.get_template");
        return file_get_contents($template_file);
    }
    
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

    protected function url($href)
    {
        return '/' . \Configuration::property('application_root') . "$href";
    }

    protected function link($url = '', $text = '', $class = '', $id = '')
    {
        $link = "<a {{id}} {{class}} {{href}} >{{text}}</a>";
        return str_replace(['{{id}}', '{{class}}', '{{href}}', '{{text}}'],
            ['id="' . $id . '"', 'class="' . $class . '"', $url != '' ? 'href="' . $url . '"' : '', $text],
            $link);
    }


}