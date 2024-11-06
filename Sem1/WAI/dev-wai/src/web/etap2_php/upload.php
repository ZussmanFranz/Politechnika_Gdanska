<?php
require_once './functions.php';

if((isset($_FILES['image'])) && ($_FILES['image']['error'] != UPLOAD_ERR_NO_FILE))
{
    if (($_POST['author'] != "") && ($_POST['title'] != "") && ($_POST['watermark'] != ""))
    {
        if (strlen($_POST['title']) > 10) {
            $_POST['title'] = substr($_POST['title'], 0, 10) . '...';
        }

        $check = check_image($_FILES['image']);
        if($check == "OK")
        {
            db_upload_image($_FILES['image']['name'], $_POST['author'], $_POST['title'], $_POST['private']);
            server_upload_image($_FILES['image'], $_POST['watermark']);
            $success = urlencode("The new image have been succesfully uploaded!");
            header("Location: index.php?success=$success");
            exit();
        }
        else
        {
            $upload_error = urlencode($check);
            header("Location: index.php?upload_error=$upload_error");
            exit();
        }
    }
    else
    {
        $upload_error = urlencode("please, enter the full data");
        header("Location: index.php?upload_error=$upload_error");
        exit();
    }
}
else
{
    $upload_error = urlencode("please, select a file");
    header("Location: index.php?upload_error=$upload_error");
    exit();
}
?>