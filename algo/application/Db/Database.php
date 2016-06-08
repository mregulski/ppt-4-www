<?php
namespace Db;

use mysqli;

class Database
{
    private $db;

    function __construct()
    {
        $this->db = $this->connect();
        \Logger::log("db connection: " . get_class($this->db), "Db\\Database.__construct()");
    }

    private function connect()
    {
        $mysqli = new mysqli('localhost', 'root', 'reshi', 'blog');
        if ($mysqli->connect_errno) {
            \Logger::log("error connecting to database: " . $mysqli->error, "[Database.connect()]");
            return false;
        } else {
            $mysqli->set_charset("utf8");
            return $mysqli;
        }
    }

    public function getUser($login)
    {
        $user = ['username' => '', 'hash' => ''];
        $stmt = $this->db->prepare("SELECT username, hash FROM users WHERE username = ?");
        $stmt->bind_param("s", $login);
        if ($stmt->execute()) {
            $stmt->bind_result($user['username'], $user['hash']);
            $stmt->fetch();
            return $user;
        }
        return false;
    }

    public function save_entry($data)
    {

        $entry['author'] = $_SESSION['user'];
        $entry['createdAt'] = date("Y-m-d H:i:s");
        $entry['title'] = strip_tags($data['entry-title']);
        $entry['content'] = strip_tags($data['entry-body']);
        \Logger::log("Saving entry:\nTitle: " . $entry['title'] . "\nAuthor: " . $entry['author'] . "\nCreatedAt: " . $entry['createdAt']
            . "\nContent: " . $entry['content'], "Database.save_entry");
        $stmt = $this->db->prepare("INSERT INTO entries(author, createdAt, title, content) VALUES (?,?,?,?)");
        $stmt->bind_param('ssss', $entry['author'], $entry['createdAt'], $entry['title'], $entry['content']);

        if ($stmt->execute()) {
            $stmt->close();
            return true;
        };
        $stmt->close();
        return false;
    }

    public function get_entries($page)
    {
        $start = $page * \Configuration::property('blog.entries_per_page');
        $end = $start + \Configuration::property('blog.entries_per_page');

        $entries = array();

        $stmt = $this->db->prepare("SELECT id, author, title, content, modifiedAt FROM entries ORDER BY createdAt DESC LIMIT ?, ?");
        $stmt->bind_param("ii", $start, $end);
        if ($stmt->execute()) {
            $stmt->bind_result($id, $author, $title, $content, $modifiedAt);
            while ($stmt->fetch()) {
                $entry = [
                    'id' => $id,
                    'author' => $author,
                    'title' => $title,
                    'content' => $content,
                    'modifiedAt' => $modifiedAt
                ];
//                    ob_start();
//                    var_dump($entry);
//                    \Logger::log(ob_get_clean(), "Db\\Database.getEntries()");
                $entries[] = $entry;
            }
        }
        return $entries;
    }

    public function get_entry($id)
    {
        $stmt = $this->db->prepare("SELECT id, author, title, content, modifiedAt FROM entries WHERE id = ?");
        $stmt->bind_param("i", $id);
        if ($stmt->execute()) {
            $stmt->bind_result($id, $author, $title, $content, $modifiedAt);
            $stmt->fetch();
            return [
                'id' => $id,
                'author' => $author,
                'title' => $title,
                'content' => $content,
                'modifiedAt' => $modifiedAt
            ];
        }
        return false;
    }


    public function update_entry($id, $data)
    {
        $entry['id'] = $id;
        $entry['title'] = strip_tags($data['entry-title']);
        $entry['content'] = strip_tags($data['entry-body']);

        $stmt = $this->db->prepare("UPDATE entries SET title = ?, content = ? WHERE id = ?");
        $stmt->bind_param('ssi', $entry['title'], $entry['content'], $id);

        $status = $stmt->execute();
        $stmt->close();
        return $status;
    }

    public function delete_entry($id)
    {
        $stmt = $this->db->prepare("DELETE FROM entries WHERE id = ?");
        $stmt->bind_param('i', $id);
        $status = $stmt->execute();
        $stmt->close();
        return $status;
    }
}


?>