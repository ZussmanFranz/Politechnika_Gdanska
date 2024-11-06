<?php

require_once 'functions.php';

session_start();

$db = get_db();
$products = $db->products->find();

clear_cart();

?>
<!DOCTYPE html>
<html>
<head>
    <title>Produkty</title>
    <link rel="stylesheet" href="styles.css"/>
</head>
<body>
<h1>Produkty</h1>

<table>
    <thead>
    <tr>
        <th>Nazwa</th>
        <th>Cena</th>
    </tr>
    </thead>

    <tbody>
    <?php if ($db->products->count()): ?>
        <?php foreach ($products as $product): ?>
            <tr>
                <td>
                    <a href="view.php?id=<?= $product['_id'] ?>"><?= $product['name'] ?></a>
                </td>
                <td><?= $product['price'] ?> PLN</td>
            </tr>
        <?php endforeach ?>
    <?php else: ?>
        <tr>
            <td colspan="3">Brak produktów</td>
        </tr>
    <?php endif ?>
    </tbody>

    <tfoot>
    <tr>
        <td>Łącznie produktów: <?= $db->products->count() ?></td>
        <td></td>
    </tr>
    </tfoot>
</table>

<?php
include 'cart.php';
?>

</body>
</html>
