<?php

require_once 'functions.php';
use MongoDB\BSON\ObjectID;


if (!empty($_GET['id'])) {
    $id = $_GET['id'];

    $db = get_db();
    $product = $db->products->findOne(['_id' => new ObjectID($id)]);

    if ($product == null) {
        http_response_code(404);
        exit;
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Produkt</title>
    <link rel="stylesheet" href="styles.css"/>
</head>
<body>

<h1><?= $product['name'] ?></h1>

<p>Cena: <?= $product['price'] ?> PLN</p>

<p class="description"><?= $product['description'] ?></p>

<a href="index.php">&laquo; Wróć</a>

</body>
</html>
