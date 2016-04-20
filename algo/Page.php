<?php
require_once('template/header.php');
require_once('template/footer.php');
require_once('template/template.php');
$Pages = [
    ['id' => 1,  'href' => 'euclid.php',      'name' => 'Algorytm Euklidesa' ],
    ['id' => 2,  'href' => 'ext_euclid.php',  'name' => 'Rozszerzony Algorytm Euklidesa' ],
    ['id' => 3,  'href' => 'prime.php',       'name' => 'Test pierwszości' ],
    ['id' => 4,  'href' => 'sieve.php',       'name' => 'Sito Erastotenesa' ],
    ['id' => 5,  'href' => 'insert_sort.php', 'name' => 'Sortowanie przez wstawianie' ],
    ['id' => 6,  'href' => 'merge_sort.php',  'name' => 'Sortowanie przez scalanie' ],
    ['id' => 7,  'href' => 'bin_search.php',  'name' => 'Wyszukiwanie binarne' ],
    ['id' => 8,  'href' => 'hanoi.php',       'name' => 'Wieże Hanoi' ],
    ['id' => 9,  'href' => 'queens.php',      'name' => 'Problem hetmanów' ],
    ['id' => 10, 'href' => 'knight.php',      'name' => 'Problem skoczka szachowego' ]
];

class AlgorithmPage {
    private $id = -1;
    private $title = '';

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
        $head = (string) str_replace("{{TITLE}}", (string) $this->title, $Header);
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
