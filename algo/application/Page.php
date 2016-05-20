<?php
namespace Algorithm;
require_once('Config.php');
$NavData = [
    ['id' => 0,  'href' => '/algo/',       'name' => 'Strona główna'],
    ['id' => 1,  'href' => 'euclid',      'name' => 'Algorytm Euklidesa'],
    ['id' => 2,  'href' => 'euclid-extended',  'name' => 'Rozszerzony Algorytm Euklidesa'],
    ['id' => 3,  'href' => 'prime-test',       'name' => 'Test pierwszości'],
    ['id' => 4,  'href' => 'erastotenes-sieve',       'name' => 'Sito Erastotenesa'],
    ['id' => 5,  'href' => 'insert-sort', 'name' => 'Sortowanie przez wstawianie'],
    ['id' => 6,  'href' => 'merge-sort',  'name' => 'Sortowanie przez scalanie'],
    ['id' => 7,  'href' => 'binary-search',  'name' => 'Wyszukiwanie binarne'],
    ['id' => 8,  'href' => 'towers-hanoi',       'name' => 'Wieże Hanoi'],
    ['id' => 9,  'href' => 'queens-problem',      'name' => 'Problem hetmanów'],
    ['id' => 10, 'href' => 'knights-tour',      'name' => 'Problem skoczka szachowego']
];

class AlgorithmPage {
    private $template;
    private $id = -1;
    private $title = "";
    private $scripts = [];
    private $styles = [];
    private $content = "";

    function __construct($id, $title) {
        $this->id = $id;
        $this->title = $title;
        $this->template  = file_get_contents('application/template/template.html');
    }

    static function getId($href) {
        global $NavData;
        foreach ($NavData as $key => $val) {
            if($NavData[$key]['href'] === $href) {
                return $NavData[$key]['id'];
            }
        }
    }

    function SetContent($content) {
        $this->content = $content;
        return $this;
    }

    function RegisterScript($script) {
        $this->scripts[] = $script;
        return $this;
    }

    function RegisterStyle($style) {
        $this->styles[] = $style;
        return $this;
    }

    function Render($visitorCount) {
        $scripts = $this->ScriptBlock();
        $styles = $this->StyleBlock();
        $menuitems = $this->GenerateMenu();
        return $this->GetHTML($scripts, $styles, $menuitems, $visitorCount);
    }

    private function GetHTML($scripts, $styles, $menuitems, $visitorCount) {
        $styleDir = Config['StylePath'];
        $resDir = Config['ResPath'];
        $html = str_replace(
            ["{{Title}}", "{{Scripts}}", "{{Styles}}",
                "{{MenuItems}}", "{{PageContent}}", "{{StylesDir}}", "{{ResDir}}",
                "{{VisitCounter}}"],
            [$this->title, $scripts, $styles, $menuitems,$this->content,
                $styleDir, $resDir, $visitorCount],
            $this->template);
        return $html;
    }

    private function ScriptBlock() {
        $scriptTags = "";
        foreach($this->scripts as $script) {
            $scriptTags .= "<script src='{$script}'></script>\n";
        }
        unset($script);
        return $scriptTags;
    }

    private function StyleBlock() {
        $styleTags = "";
        foreach($this->styles as $style) {
            $styleTags .= "<link rel='stylesheet' href='$style'/>\n";
        }
        unset($style);
        return $styleTags;
    }

    public function Footer() {
        global $Footer;
        return $Footer;
    }
    private function GenerateMenu() {
        global $NavData;
        $menu_class = 'algorytm';
        $menu_entry = "<li class='$menu_class {{Class}}'><a href='{{Href}}' class='{{Class}}'>{{Name}}</a></li>";
        $menu = "<ul>\n";
        for($i = 0; $i < count($NavData); $i++) {
            $classes="";
            if((int) $NavData[$i]["id"] === $this->id) {
                $classes.="active";
            };
            $element = (string) str_replace("{{Href}}", (string) $NavData[$i]["href"], $menu_entry);
            $element = (string) str_replace("{{Name}}", (string) $NavData[$i]["name"], $element);
            $element = (string) str_replace("{{Class}}", (string) $classes, $element);
            $menu .= $element."\n";

        };
        $menu .= "</ul>\n";
        return $menu;
    }

}
?>
