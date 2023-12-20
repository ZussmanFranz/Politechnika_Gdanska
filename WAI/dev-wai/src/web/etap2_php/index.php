<?php

require_once 'functions.php';
session_start();

$db = get_db();

if (!isset($_SESSION['user']))
{
    header("Location: account.php");
    exit();
}

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
                    $images = $db->images->find();

                    foreach ($images as $image) {
                        echo '<a href="./zdjecia/watermarks/'.$image['name'].'"><div class="image_header">'.$image['title'].'</div><img src="./zdjecia/miniatures/' . $image['name'] . '" alt="'.$image['title'].'" /></a>';
                    }
                ?>
            </div>
        </section>
    </div>
    
    <form action="upload.php" method="POST" enctype="multipart/form-data">
        <table id="image_upload">
            <th colspan="3">Upload new image!</th>
            <tr>
                <td colspan="3"><input type="file" name="image" id="zdjecie">
                <?php
                    if(isset($_GET['upload_error']))
                    {
                        echo '<div id="incorrect">'.$_GET['upload_error'].'</div>';
                        unset($_GET['upload_error']);
                    }
                    elseif(isset($_GET['success']))
                    {
                        echo '<div id="success">'.$_GET['success'].'</div>';
                        unset($_GET['success']);
                    }
                ?>
                </td>
            </tr>
            <tr>
                <td>Author name: <?php echo '<input type="text" name="author" value="'.$_SESSION['user']['login'].'">'?></td>
                <td>Title: <input type="text" name="title"/></td>
                <td>Watermark: <input type="text" name="watermark"/></td>
            </tr>
            <tr>
                <td colspan="2">
                    Private: <br>
                    <label for="private">Yes: <input type="radio" name="private" value="yes"></label>
                    <label for="private">No: <input type="radio" name="private" value="no" checked></label>
                </td>
                <td><input type="submit" id="submit_photo" value="Upload"></td>
            </tr>
        </table>
    </form>

    <div id="skull"><a href="#header"><img src="./img/servo-skull.svg" alt="Go to top"></a></div>
    <footer id="footer">Yauheni Pyryeu, 023.M3</footer>
</div>
</body>
</html>