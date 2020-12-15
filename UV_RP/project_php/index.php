<?php
if (isset($_GET['iuv'])) {
	$myfile = fopen("./data.txt", "a") or die("Unable to open file!");
	$txt = $_GET['iuv'].PHP_EOL;
	fwrite($myfile, $txt);
	fclose($myfile);
} else {
    // Fallback behaviour goes here
}
