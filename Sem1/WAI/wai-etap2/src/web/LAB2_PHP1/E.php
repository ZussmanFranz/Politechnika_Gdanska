<?php

if(isset($_POST['E_typ'])){
    $rodzaj = $_POST['E_typ'];
    //echo "OK, odebrałem: ". $rodzaj;
    if($rodzaj == "P") {$directory = './E_positive';}
    elseif($rodzaj == "N") {$directory = './E_negative';}
    else {
        exit;
    }

    $scanned_directory = array_diff(scandir($directory), array('..', '.'));
    //print_r($scanned_directory);
    foreach($scanned_directory as $plik) {
        echo '<img src="' . $directory . '/' . $plik . '" alt="emotka"/><br/> ';
    }
}

?>
