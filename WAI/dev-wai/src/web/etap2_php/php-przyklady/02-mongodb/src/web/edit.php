<?php

require_once 'functions.php';
use MongoDB\BSON\ObjectID;


$db = get_db();

$product = [
    'name' => null,
    'price' => null,
    'description' => null,
    '_id' => null
];

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!empty($_POST['name']) &&
        !empty($_POST['price']) &&
        !empty($_POST['description'])
    ) {
        $product = [
            'name' => $_POST['name'],
            'price' => (int)$_POST['price'],
            'description' => $_POST['description']
        ];

        if (empty($_POST['id'])) {
            $db->products->insertOne($product);
        } else {
            $id = $_POST['id'];
            $db->products->replaceOne(['_id' => new ObjectID($id)], $product);
        }

        header('Location: index.php');
        exit;
    }

} else {
    if (!empty($_GET['id'])) {
        $id = $_GET['id'];
        $product = $db->products->findOne(['_id' => new ObjectID($id)]);
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Edycja</title>
    <link rel="stylesheet" href="styles.css"/>
</head>
<body>

<form method="post">
    <label>
        <span>Nazwa:</span>
        <input type="text" name="name" value="<?= $product['name'] ?>" required/>
    </label>
    <label>
        <span>Cena:</span>
        <input type="text" name="price" value="<?= $product['price'] ?>" required/>
    </label>

    <textarea name="description" placeholder="Opis..."><?= $product['description'] ?></textarea>

    <input type="hidden" name="id" value="<?= $product['_id'] ?>">

    <div>
        <a href="index.php" class="cancel">Anuluj</a>
        <input type="submit" value="Zapisz"/>
    </div>
</form>

</body>
</html>
