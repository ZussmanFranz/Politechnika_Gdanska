<!DOCTYPE html>
<html>
<head>
    <title>Produkt</title>
    <link rel="stylesheet" href="static/css/styles.css"/>
</head>
<body>

<h1><?= $product['name'] ?></h1>

<p>Cena: <?= $product['price'] ?> PLN</p>

<p class="description"><?= $product['description'] ?></p>

<form action="cart/add" method="post" class="wide">
    <input type="hidden" name="id" value="<?= $product['_id'] ?>"/>

    <div>
        <a href="products" class="cancel">&laquo; Wróć</a>
        <input type="submit" name="add_to_cart" value="Do koszyka"/>
    </div>
</form>

<?php dispatch($routing, '/cart') ?>

</body>
</html>
