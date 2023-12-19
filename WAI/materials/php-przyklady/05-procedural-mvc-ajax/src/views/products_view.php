<!DOCTYPE html>
<html>
<head>
    <title>Produkty</title>
    <?php include "includes/head.inc.php"; ?>
</head>
<body>

<table>
    <thead>
    <tr>
        <th>Nazwa</th>
        <th>Cena</th>
        <th>Operacje</th>
    </tr>
    </thead>

    <tbody>
    <?php if (count($products)): ?>
        <?php foreach ($products as $product): ?>
            <tr>
                <td>
                    <a href="view?id=<?= $product['_id'] ?>"><?= $product['name'] ?></a>
                </td>
                <td><?= $product['price'] ?> PLN</td>
                <td>
                    <a href="edit?id=<?= $product['_id'] ?>">Edytuj</a> |
                    <a href="delete?id=<?= $product['_id'] ?>">Usuń</a>
                </td>
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
        <td colspan="2">Łącznie: <?= count($products) ?></td>
        <td>
            <a href="edit">nowy produkt</a>
        </td>
    </tr>
    </tfoot>
</table>

<?php dispatch($routing, '/cart') ?>

<?php include "includes/footer.inc.php"; ?>

</body>
</html>
