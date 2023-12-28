<?php

require_once 'functions.php';
session_start();

$login = $_SESSION['login'];

$db = get_db();

if (!isset($_SESSION['user']))
{
    header("Location: account.php");
    exit();
}

if(!isset($_GET['page']))
{
    $page = 0;
}
else
{
    $page = $_GET['page'];
}

$db = get_db();

$page_size = 3;
$pages_max = db_count_pages($page_size, $login);

if($page < 0)
{
    $page = $pages_max;
}
elseif($page > $pages_max)
{
    $page = 0;
}

$images = db_get_images($login, $page, $page_size);

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
                    foreach ($images as $image) {
                        echo '<a href="./images/watermarks/'.$image['name'].'" class="gallery_images"><div class="image_header">'.$image['title'].'<br><div class="image_author">Author: '.$image['author'].'</div></div><img src="./images/miniatures/' . $image['name'] . '" alt="'.$image['title'].'"/></a>';
                    }
                ?>
            </div>
        </section>
        <?php
        if($pages_max > 0)
        {
            echo '<div id="paging_controller">
                <a href="index.php?page='.($page - 1).'" id="left"><h3>< </h3></a>
                <h3 id="center">'.($page + 1).'</h3>
                <a href="index.php?page='.($page + 1).'" id="right"><h3> ></h3></a>
            </div>';
        }
        ?>
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
                <td>Author name: <?= '<input type="text" name="author" value="'.$_SESSION['user']['login'].'">'?></td>
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