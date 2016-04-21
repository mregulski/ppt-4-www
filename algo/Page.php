<?php
require_once('template/header.php');
require_once('template/footer.php');
require_once('template/template.php');

$Pages = [
    ['id' => 0,  'href' => 'index.php',       'name' => 'Index', 'scripts' => [], 'styles' => []],
    ['id' => 1,  'href' => 'euclid.php',      'name' => 'Algorytm Euklidesa',             'scripts' => [], 'styles' => [] ],
    ['id' => 2,  'href' => 'ext_euclid.php',  'name' => 'Rozszerzony Algorytm Euklidesa', 'scripts' => [], 'styles' => [] ],
    ['id' => 3,  'href' => 'prime.php',       'name' => 'Test pierwszości',               'scripts' => [], 'styles' => [] ],
    ['id' => 4,  'href' => 'sieve.php',       'name' => 'Sito Erastotenesa',              'scripts' => [], 'styles' => [] ],
    ['id' => 5,  'href' => 'insert_sort.php', 'name' => 'Sortowanie przez wstawianie',    'scripts' => [], 'styles' => [] ],
    ['id' => 6,  'href' => 'merge_sort.php',  'name' => 'Sortowanie przez scalanie',      'scripts' => ['mergeSort.js'], 'styles' => [] ],
    ['id' => 7,  'href' => 'bin_search.php',  'name' => 'Wyszukiwanie binarne',           'scripts' => [], 'styles' => [] ],
    ['id' => 8,  'href' => 'hanoi.php',       'name' => 'Wieże Hanoi',                    'scripts' => [], 'styles' => [] ],
    ['id' => 9,  'href' => 'queens.php',      'name' => 'Problem hetmanów',               'scripts' => [], 'styles' => [] ],
    ['id' => 10, 'href' => 'knight.php',      'name' => 'Problem skoczka szachowego',     'scripts' => [], 'styles' => [] ]
];
$Config = [
    "ScriptPath" => 'scripts',
    "StylePath" => 'styles'
];

class AlgorithmPage {
    private $id = -1;
    private $title = "";

    function __construct($id, $title) {
        $this->id = $id;
        $this->title = $title;
    }

    function RenderPage($content) {
        global $Template;
        $header = (string) $this->Header();
        $footer = (string) $this->Footer();
        $menu = (string) $this->GenerateMenu();
        $page = str_replace("{{Header}}", $header, $Template);
        $page = str_replace("{{MenuItems}}", $menu, $page);
        $page = str_replace("{{Footer}}", $footer, $page);
        $page = str_replace("{{PageContent}}", $content, $page);
        echo $page;

    }

    private function Header() {
        global $Header;
        global $Pages;
        global $Config;
        $scripts = "";
        foreach($Pages[$this->id]['scripts'] as $script) {
            $scripts .= "<script src='{$Config["ScriptPath"]}/{$script}'></script>\n";
        }
        unset($script);
        $styles = "";
        foreach($Pages[$this->id]['styles'] as $style) {
            $styles .= "<link rel='stylesheet' src='{$Config["StylePath"]}/$style'/>\n";
        }
        unset($style);
        $head = (string) str_replace("{{Scripts}}", (string) $scripts , $Header);
        $head = (string) str_replace("{{Styles}}", (string) $styles, $head);
        $head = (string) str_replace("{{Title}}", (string) $this->title, $head);
        $head .= "\n";
        return $head;
    }

    private function Footer() {
        global $Footer;
        return $Footer;
    }
    private function GenerateMenu() {
        global $Pages;
        $menu_class = 'algorytm';
        $menu_entry = "<li class='$menu_class'><a href='{{Href}}' class='{{Class}}'>{{Name}}</a></li>";
        $menu = "<ul>\n";
        for($i = 0; $i < count($Pages); $i++) {
            $classes="";
            if((int) $Pages[$i]["id"] === $this->id) {
                $classes.="active";
            };
            $element = (string) str_replace("{{Href}}", (string) $Pages[$i]["href"], $menu_entry);
            $element = (string) str_replace("{{Name}}", (string) $Pages[$i]["name"], $element);
            $element = (string) str_replace("{{Class}}", (string) $classes, $element);
            $menu .= $element."\n";

        };
        $menu .= "</ul>\n";
        return $menu;
    }

}
?>
