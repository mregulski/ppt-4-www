<?php
    class Logger {
        static function log($message, $who="") {
            $message = date_format(date_create(), "[Y-m-d H:i:s] ").$who." ".$message."\n";
            $log = fopen(ini_get('error_log'), 'a');
            fwrite($log, $message);
            fclose($log);
        }
    }
?>