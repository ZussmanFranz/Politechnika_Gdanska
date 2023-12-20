<?php

require_once 'functions.php';
session_start();

$db = get_db();

if (!isset($_SESSION['user']))
{
    header("Location: account.php");
    exit();
}

/*if (isset($_SESSION['logout']))
{
    unset($_SESSION['logout']);
    session_unset();
    header("Location: index.php");
    exit();
}*/

$login = $_SESSION['login'];

?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./style_php.css">
    <title>PHP</title>
</head>
<body>

<div id = "main" class="projects">
    <header id="header"><q>Hello, <?=  $login ?></q></header>

    <a href="./logout.php" id="log_out">Log out</a>
    
    <div id="online_gallery">
        <section>
            <div class="gallery_detailed">
                <?php
                    $db = get_db();
                    $photos = $db->images->find();

                    foreach ($photos as $photo) {
                        echo '<a href="./zdjecia/watermarks/'.$photo['name'].'"><img src="./zdjecia/miniatures/' . $photo['name'] . '" alt="'.$photo['title'].'" /></a>';
                    }
                ?>
            </div>
        </section>
    </div>
    <!-- dodawanie nowych zdjęć!!! -->
    <form action="upload.php">
        <table>
            <th>Upload new image!</th>
            <tr>
                <td><input type="file" name="file" id="zdjecie"></td>
            </tr>
            <tr>
                <td><?php echo '<input type="text" name="author" value="'.$_SESSION['user']['login'].'">'?></td>
            </tr>
            <tr>
                <td><input type="text" name="title" placeholder="title"></td>
            </tr>
            <tr>
                <td>
                    <label for="private" value="Private: ">
                        <input type="radio" name="private" value="yes">
                        <input type="radio" name="private" value="no">
                    </label>
                </td>
            </tr>
            <tr>
                <td><input type="submit" value="Upload"></td>
            </tr>
        </table>
    </form>
    <div id="skull"><a href="#header"><img src="./img/servo-skull.svg" alt="Go to top"></a></div>
    <footer id="footer">Yauheni Pyryeu, 023.M3</footer>
</div>
</body>
</html>