<!DOCTYPE html>
<html>
<head>
    <title>Edycja</title>
    <link rel="stylesheet" href="static/css/styles.css"/>
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
        <a href="products" class="cancel">Anuluj</a>
        <input type="submit" value="Zapisz"/>
    </div>
</form>

</body>
</html>
