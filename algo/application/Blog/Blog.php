<?php
namespace Blog;
require_once("application/Db/Database.php");
require_once("application/Page.php");

use Db\Database;
use Session\Session;

class BlogPage extends \Page
{
    private $edit_mode = false;
    private $template;
    private $page;
    private $post;

    public function __construct($edit_mode, $page_number, $post_number)
    {
        $this->edit_mode = $edit_mode;
        $this->page = $page_number;
        if ($this->edit_mode) {
            $this->template = \Configuration::property('template.editor');
            $this->post = $post_number;
        } else {
            $this->template = \Configuration::property('template.blog');
        }
    }

    public function render($visit_count)
    {
        //get entries for page_num
        $template = file_get_contents($this->template);
        $page = str_replace(["{{Title}}", "{{Scripts}}", "{{Styles}}",
            "{{MenuItems}}", "{{PageContent}}", "{{StylesDir}}", "{{ResDir}}", "{{ScriptDir}}",
            "{{VisitCounter}}", "{{Feedback}}"],
            ["Blog", '', '', $this->GenerateMenu(), $this->get_content(), \Configuration::property('style_path'),
                \Configuration::property('res_path'), \Configuration::property('script_path'), $visit_count, ''],
            $template);
        return $page;
    }

    private function get_content()
    {
        if ($this->edit_mode) {
            $title = '';
            $entry_body = '';
            $heading = 'Nowy wpis';
            $method = '';
            if ($this->post) {
                $entry = (new Database())->get_entry($this->post);
                $title = $entry['title'];
                $entry_body = $entry['content'];
                $heading = "Edytuj wpis";
                $method = 'PATCH';

            }
            return str_replace(["{{Title}}", '{{Entry}}', '{{Heading}}', '{{Method}}'],
                [$title, $entry_body, $heading, $method],
                file_get_contents(\Configuration::property("template.blog_editor")));
        }
        return $this->get_entries();

    }

    private function get_edit_link($id)
    {
//            $link =  "<div><a class='blog-edit' href='" . $this->link("blog/entry/" . $id ) ."'>Edytuj</a></div>";
        $url = $this->link("blog/entry/" . $id);
        $link = "<form class='blog-edit' action='$url' method='GET'><input type='submit' value='Edytuj'/></form>";
//            \Logger::log("id: $id. edit link: " . $this->link("blog/' . $id . '/edit"), "Blog.get_edit_link()");
        return $link;
    }

    private function get_remove_link($id)
    {
        $url = $this->link("blog/entry/" . $id);
        $link = "<form class='blog-remove' action='$url' method='POST'><input type='hidden' name='method' value='DELETE'/><input type='submit' value='Usuń'/></form>";
        return $link;
    }

    private function get_entries()
    {
        $db = new Database();
        $entries = $db->get_entries($this->page);
        $entry = file_get_contents(\Configuration::property("template.blog_entry"));
        $page = '';

        foreach ($entries as $e) {
//                \Logger::log($e['author']. ' ' . $e['modifiedAt']. ' ' . $e['title'] . ' ' . $e['content'], 'Blog.get_entries');
            $elem = str_replace(["{{Author}}", "{{ModifiedAt}}", "{{Title}}", "{{Content}}"],
                [$e['author'], $e['modifiedAt'], $e['title'], $e['content']],
                $entry);
            if (Session::check()) {
                $elem = str_replace("{{EditLink}}", $this->get_edit_link($e['id']), $elem);
                $elem = str_replace("{{RemoveLink}}", $this->get_remove_link($e['id']), $elem);
            } else {
                $elem = str_replace("{{EditLink}}", '', $elem);
                $elem = str_replace("{{RemoveLink}}", '', $elem);
            }
            $page .= $elem;
        }
        return $page;
    }

    private function GenerateMenu()
    {
        $menu_entry = "<li class='{{Class:active}}'><a href='{{Href}}' class='{{Class:active}}'>{{Name}}</a></li>";
        $menu = "<ul>\n";
        $menu .= str_replace(
            ['{{Href}}', '{{Class:active}}', '{{Name}}'],
            [$this->link(''), '', 'Strona główna'],
            $menu_entry);
        $menu .= str_replace(['{{Href}}', '{{Class:active}}', '{{Name}}'],
            [$this->link('blog'), $this->edit_mode ? '' : 'active', 'Blog'], $menu_entry);
        if (!Session::check()) {
            $menu .= str_replace(['{{Href}}', '{{Class:active}}', '{{Name}}'],
                [$this->link('login'), $this->edit_mode ? 'active' : '', 'Zaloguj'], $menu_entry);
        } else {
            $menu .= str_replace(['{{Href}}', '{{Class:active}}', '{{Name}}'],
                [$this->link('blog/new'), $this->edit_mode ? 'active' : '', 'Dodaj wpis'], $menu_entry);
            $menu .= str_replace(['{{Href}}', '{{Class:active}}', '{{Name}}'],
                [$this->link('logout'), '', 'Wyloguj'], $menu_entry);

        }
        $menu .= "</ul>\n";
        return $menu;
    }

}

?>