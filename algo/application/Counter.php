<?php
class Counter {
    private $counterFile = "visitors.txt";
    private $count = 0;
    function __construct() {
        if(!file_exists($this->counterFile)) {
            $fp = fopen($this->counterFile, 'w');
            fwrite($fp, 0);
            fclose($fp);
        }
    }

    function update() {
        $fp = fopen($this->counterFile, 'r');
        $data = fread($fp, filesize($this->counterFile));
        $this->count = $data + 1;

        fclose($fp);
        $fp = fopen($this->counterFile, 'w');
        fwrite($fp, $this->count);
        fclose($fp);
    }

    function getCount() {
        return $this->count;
    }
}
?>
