<?php

require_once 'vendor/autoload.php'; // Подключаем автозагрузчик Composer

// łączymy się z MongoDB
$client = new MongoDB\Client("mongodb://http://192.168.56.10:27017"); //failed to parse ! (????)

// wybieramy bazę danych
$database = $client->selectDatabase('имя_базы_данных');

// wybieramy kolekcję
$collection = $database->selectCollection('имя_коллекции');

//$result = $collection->find();

/*foreach ($result as $document) {
    var_dump($document);
}*/
?>
