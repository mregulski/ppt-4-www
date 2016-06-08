<?php
namespace Algorithm;

require_once('Config.php');
require_once('Page.php');
$NavData = [
    ['id' => 0, 'href' => '/algo/', 'name' => 'Strona główna'],
    ['id' => 1, 'href' => 'euclid', 'name' => 'Algorytm Euklidesa'],
    ['id' => 2, 'href' => 'euclid-extended', 'name' => 'Rozszerzony Algorytm Euklidesa'],
    ['id' => 3, 'href' => 'prime-test', 'name' => 'Test pierwszości'],
    ['id' => 4, 'href' => 'erastotenes-sieve', 'name' => 'Sito Erastotenesa'],
    ['id' => 5, 'href' => 'insert-sort', 'name' => 'Sortowanie przez wstawianie'],
    ['id' => 6, 'href' => 'merge-sort', 'name' => 'Sortowanie przez scalanie'],
    ['id' => 7, 'href' => 'binary-search', 'name' => 'Wyszukiwanie binarne'],
    ['id' => 8, 'href' => 'towers-hanoi', 'name' => 'Wieże Hanoi'],
    ['id' => 9, 'href' => 'queens-problem', 'name' => 'Problem hetmanów'],
    ['id' => 10, 'href' => 'knights-tour', 'name' => 'Problem skoczka szachowego']
];


class AlgorithmPage extends \Page
{
    private $template;
    private $id = -1;
    private $title = "";
    private $content = "";

    function __construct($id, $title)
    {
        $this->id = $id;
        $this->title = $title;
        $this->template = file_get_contents(\Configuration::property('template.algorithm'));
    }

    static function getId($href)
    {
        global $NavData;
        foreach ($NavData as $key => $val) {
            if ($NavData[$key]['href'] === $href) {
                return $NavData[$key]['id'];
            }
        }
    }

    function SetContent($content)
    {
        $this->content = $content;
        return $this;
    }

    function Render($visitorCount)
    {
        $scripts = $this->ScriptBlock();
        $styles = $this->StyleBlock();
        $menuitems = $this->GenerateMenu();
        return $this->GetHTML($scripts, $styles, $menuitems, $visitorCount);
    }

    private function GetHTML($scripts, $styles, $menuitems, $visitorCount)
    {
        $styleDir = \Configuration::property("style_path");
        $resDir = \Configuration::property("res_path");
        $scriptDir = \Configuration::property("script_path");
        $html = str_replace(
            ["{{Title}}", "{{Scripts}}", "{{Styles}}",
                "{{MenuItems}}", "{{PageContent}}", "{{StylesDir}}", "{{ResDir}}",
                "{{ScriptDir}}", "{{VisitCounter}}", "{{Feedback}}"],
            [$this->title, $scripts, $styles, $menuitems, $this->content,
                $styleDir, $resDir, $scriptDir, $visitorCount, $this->GetFeedback()],
            $this->template);
        return $html;
    }

    private function GetFeedback()
    {
        if ($this->id == 0) {
            return "";
        }
        return file_get_contents(\Configuration::property("template.feedback"));
    }

    public function Footer()
    {
        global $Footer;
        return $Footer;
    }

    private function GenerateMenu()
    {
        global $NavData;
        $menu_entry = "<li class='{{Class:active}}'><a href='{{Href}}' class='{{Class:active}}'>{{Name}}</a></li>";
        $menu = "<ul>\n";

        $menu .= str_replace(['{{Class:active}}', '{{Href}}', '{{Name}}'],
            [$this->id == 0 ? 'active' : '', \Configuration::property('application_root'), 'Strona główna'],
            $menu_entry);
        $menu .= str_replace(['{{Class:active}}', '{{Href}}', '{{Name}}'],
            ['', $this->link('blog'), 'Blog'],
            $menu_entry);
        for ($i = 1; $i < count($NavData); $i++) {
            $classes = "";
            if ((int)$NavData[$i]["id"] === $this->id) {
                $classes .= "active";
                $element = (string)str_replace("href='{{Href}}'", "", $menu_entry);
            } else {
                $element = (string)str_replace("{{Href}}", (string)$NavData[$i]["href"], $menu_entry);
            }
            $element = (string)str_replace("{{Name}}", (string)$NavData[$i]["name"], $element);
            $element = (string)str_replace("{{Class:active}}", (string)$classes, $element);
            $menu .= $element . "\n";

        };


        $menu .= "</ul>\n";
        return $menu;
    }

}

?>
