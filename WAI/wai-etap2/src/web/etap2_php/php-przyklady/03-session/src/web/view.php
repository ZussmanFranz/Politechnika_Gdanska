<?php

require_once 'functions.php';
use MongoDB\BSON\ObjectID;

session_start();


$db = get_db();

clear_cart();

if (!empty($_REQUEST['id'])) {
    $id = $_REQUEST['id'];
    $product = $db->products->findOne(['_id' => new ObjectID($id)]);

    if ($product == null) {
        http_response_code(404);
        exit;
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['add_to_cart'])) {

    $cart = &get_cart();

    if (isset($cart[$id])) {
        $amount = $cart[$id]['amount'] + 1;
    } else {
        $amount = 1;
    }

    $cart[$id] = ['name' => $product['name'], 'amount' => $amount];

    header('Location: ' . $_SERVER['HTTP_REFERER']);
    exit;
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

<form method="post" class="wide">
    <input type="hidden" name="id" value="<?= $id ?>"/>

    <div>
        <a href="index.php" class="cancel">&laquo; Wróć</a>
        <input type="submit" name="add_to_cart" value="Do koszyka"/>
    </div>
</form>

<?php
include 'cart.php';
?>

</body>
</html>
