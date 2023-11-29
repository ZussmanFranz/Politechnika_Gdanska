<?php

function robAJAX($rodzaj) {
    if ($rodzaj == "P") {$directory = './E_positive';}
    elseif ($rodzaj == "N") {$directory = './E_negative';}
    else {
        header("Location: 1.html");
        exit;
    }

    $scanned_directory = array_diff(scandir($directory),
array('..', '.'));

    $zdjecia = '';

    foreach ($scanned_directory as $plik) {
        $zdjecia= $zdjecia . '<img src="' . $directory . '/'.
        $plik . '" alt="emotikonka" ><br />';
        }

    return $zdjecia;        
}

?>