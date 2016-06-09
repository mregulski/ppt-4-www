<?php
namespace Blog;
require_once("application/Db/Database.php");
require_once("application/Page.php");
require_once("application/Util.php");

use Db\Database;
use Session\Session;

class BlogPage extends \Page
{
    private $edit_mode = false;
    private $template;
    private $page_number;
    private $post;
    private $db;

    public function __construct($edit_mode, $page_number, $post_number)
    {
        $this->db = new Database();
        $this->edit_mode = $edit_mode;
        $this->page_number = $page_number;
        $this->post = $post_number;
        \Logger::log("Creating BlogPage.\nEdit: $edit_mode\nPage: $page_number\nEntry: $post_number",
            "BlogPage.__construct()");
        if ($this->edit_mode) {
            $this->template = $this->get_template('blog.edit');
        } else if ($post_number != null) {
            $this->template = $this->get_template('blog.single_entry');
        } else {
            $this->template = $this->get_template('blog.list');
        }
    }

    public function render($visit_count)
    {
        //get entries for page_num
        $page = str_replace(["{{Title}}", "{{Scripts}}", "{{Styles}}",
            "{{MenuItems}}", "{{PageContent}}", "{{StylesDir}}", "{{ResDir}}", "{{ScriptDir}}",
            "{{VisitCounter}}", "{{Feedback}}"],
            ["Blog", '', '', $this->generate_menu(), $this->get_content(), \Configuration::property('style_path'),
                \Configuration::property('res_path'), \Configuration::property('script_path'), $visit_count, ''],
            $this->template);
        return $page;
    }

    private function get_content()
    {
        if ($this->edit_mode) {
            $title = '';
            $entry_body = '';
            $heading = 'Nowy wpis';
            $method = '';
            $url = $this->url('blog/new');
            if ($this->post) {
                $entry = (new Database())->get_entry($this->post);
                $title = $entry['title'];
                $entry_body = $entry['content'];
                $heading = "Edytuj wpis";
                $method = 'PATCH';
                $url = $this->url('blog/entry/' . $this->post);
            }

            return str_replace(['{{submit_url}}', '{{Title}}', '{{Entry}}', '{{Heading}}', '{{Method}}', '{{blog_url}}'],
                [$url, $title, $entry_body, $heading, $method, $this->url('blog')],
                $this->get_template("blog.editor"));
        }
        if ($this->post != null) {
            return $this->get_entry();
        } else {
            return $this->get_entries() . $this->generate_pagination();
        }
    }

    private function edit_link($id)
    {
        $url = $this->url("blog/entry/" . $id . "/edit");
        $link = "<form class='blog-edit' action='$url' method='GET'><input type='submit' value='Edytuj'/></form>";
//            \Logger::log("id: $id. edit link: " . $this->link("blog/' . $id . '/edit"), "Blog.get_edit_link()");
        return $link;
    }

    private function remove_link($id)
    {
        $url = $this->url("blog/entry/" . $id);
        $link = "<form class='blog-remove' action='$url' method='POST'><input type='hidden' name='method' value='DELETE'/><input type='submit' value='Usuń'/></form>";
        return $link;
    }

    private function get_entry()
    {
        $entry = $this->db->get_entry($this->post);
        $template = $this->get_template("blog.list_entry");

        $elem = str_replace(["{{Author}}", "{{ModifiedAt}}", "{{Title}}", "{{Content}}"],
            [$entry['author'], $entry['modifiedAt'], $entry['title'], $entry['content']],
            $template);
        if (Session::check()) {
            $elem = str_replace("{{EditLink}}", $this->edit_link($entry['id']), $elem);
            $elem = str_replace("{{RemoveLink}}", $this->remove_link($entry['id']), $elem);
        } else {
            $elem = str_replace("{{EditLink}}", '', $elem);
            $elem = str_replace("{{RemoveLink}}", '', $elem);
        }

        return $elem;
    }

    private function get_entries()
    {
        $entries = $this->db->get_entries($this->page_number - 1); // human -> database
        $entry = $this->get_template("blog.list_entry");
        $page = '';

        foreach ($entries as $e) {
//                \Logger::log($e['author']. ' ' . $e['modifiedAt']. ' ' . $e['title'] . ' ' . $e['content'], 'Blog.get_entries');

            $entry_link = $this->link($this->url('blog/entry/' . $e['id']), $e['title']);
            $read_more = str_word_count($e['content']) >= \Configuration::property('blog.excerpt_length')
                ? $this->link($this->url('blog/entry/' . $e['id']), '<span class="read-more">(czytaj dalej)</span>')
                : '';

            $elem = str_replace(["{{Author}}", "{{ModifiedAt}}", "{{Title}}", "{{Content}}"],
                [$e['author'], $e['modifiedAt'], $entry_link, \Util::get_excerpt($e['content']) . $read_more],
                $entry);
            if (Session::check()) {
                $elem = str_replace("{{EditLink}}", $this->edit_link($e['id']), $elem);
                $elem = str_replace("{{RemoveLink}}", $this->remove_link($e['id']), $elem);
            } else {
                $elem = str_replace("{{EditLink}}", '', $elem);
                $elem = str_replace("{{RemoveLink}}", '', $elem);
            }
            $page .= $elem;
        }
        return $page;
    }

    private function generate_menu()
    {
        $menu_entry = "<li class='{{active}}'>{{link}}</li>";
        $menu = "<ul>\n";

        $menu .= str_replace(['{{active}}', '{{link}}'],
            ['', $this->link($this->url(''), 'Strona główna')],
            $menu_entry);
        $menu .= str_replace(['{{active}}', '{{link}}'],
            [$this->edit_mode || $this->post ? '' : 'active',
                $this->link($this->edit_mode || $this->post ? $this->url('blog') : '',
                    'Blog',
                    $this->edit_mode || $this->post ? '' : 'active')
            ],
            $menu_entry);

        if (!Session::check()) {
            $menu .= str_replace(['{{active}}', '{{link}}'],
                ['', $this->link($this->url('login'), 'Zaloguj')],
                $menu_entry);
        } else {
            $menu .= str_replace(['{{active}}', '{{link}}'],
                [$this->edit_mode && !$this->post ? 'active' : '',
                    $this->link($this->url('blog/new'), 'Dodaj wpis', $this->edit_mode ? 'active' : '')
                ],
                $menu_entry);
            $menu .= str_replace(['{{active}}', '{{link}}'],
                ['', $this->link($this->url('logout'), 'Wyloguj')],
                $menu_entry);
        }
        $menu .= "</ul>\n";
        return $menu;
    }

    private function generate_pagination()
    {
        $current = $this->page_number;
        $total_pages = $this->db->get_page_count();
        $pagination_container = $this->get_template("blog.pagination.container");

        \Logger::log("page number: $current");
        if ($current == 1) {
            $first_page = $this->page_link($current, true);
        } else {
            $first_page = $this->page_link(1, false);
        }
        if ($current == $total_pages) {
            $last_page = $this->page_link($current, true);
        } else {
            $last_page = $this->page_link($total_pages, false);
        }

        $pages = '';
        $bound_low = $total_pages > 7 ? ($current - 2 > 2 ? $current - 2 : 2) : 2;
        $bound_high = $total_pages > 7 ? ($current + 2 < $total_pages ? $current + 2 : $total_pages - 1) : $total_pages - 1;

        if ($bound_low > 2) {
            $first_page .= str_replace(["{{class}}", "href=\"{{page_url}}\"", "{{page_number}}"],
                ['pagination-filler', '', '...'],
                $this->get_template("blog.pagination.link"));
        }

        if ($bound_high < $total_pages - 1) {
            $last_page = str_replace(["{{class}}", "href=\"{{page_url}}\"", "{{page_number}}"],
                    ['pagination-filler', '', '...'],
                    $this->get_template("blog.pagination.link")) . $last_page;
        }

        for ($i = $bound_low; $i <= $bound_high; $i++) {
            $pages .= $this->page_link($i, $i == $current);
        }

        return str_replace(["{{first-page}}", "{{pages}}", "{{last-page}}"],
            [$first_page, $pages, $last_page],
            $pagination_container);
    }

    private function page_link($number, $active)
    {
        $page_link = $this->get_template("blog.pagination.link");
        if ($number == $this->page_number) {
            return str_replace(["{{class}}", "href=\"{{page_url}}\"", "{{page_number}}"],
                [$active ? 'active' : '', '', $number],
                $page_link);
        } else {
            return str_replace(["{{class}}", "{{page_url}}", "{{page_number}}"],
                [$active ? 'active' : '', $this->url('blog/' . $number), $number],
                $page_link);
        }
    }
    

}

?>