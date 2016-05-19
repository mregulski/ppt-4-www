<?php
namespace Algorithm;
require_once('application/Page.php');

$content = file_get_contents('application/content/merge_sort.html');
$page = new AlgorithmPage(6, "Algorytmy", $content);
$page->RegisterScript('scripts/mergeSort.js');
?>
<?=$page->Render();?>
