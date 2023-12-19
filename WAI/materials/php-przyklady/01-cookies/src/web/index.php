<?php

if (isset($_POST['imie'])) {
    $imie = $_POST['imie'];

    setcookie("imie", $imie, time() + 60 * 60, "/");
    setcookie("imie_w_sesji_przegladarki", $imie);

    header("Location: index.php");
    exit;

} elseif (isset($_POST['reset'])) {
    setcookie("imie_w_sesji_przegladarki", false);
    setcookie("imie", '', time() - 60 * 60, '/');

    header("Location: index.php");
    exit;

} elseif (isset($_COOKIE['imie'])) {
    $imie = $_COOKIE['imie'];
}

?>
<!DOCTYPE html>
<html>
<head>
    <title>Pliki cookies</title>
</head>
<body>

<?php if (isset($imie)): ?>
    <h1>Witaj, <?= $imie ?>!</h1>
    <form method="post">
        <input type="submit" name="reset" value="Zmień imię">
    </form>
<?php else: ?>
    <form method="post">
        <label>
            Jak masz na imię?
            <input type="text" name="imie"/>
        </label>
        <input type="submit" value="OK">
    </form>
<?php endif ?>

</body>
</html>
