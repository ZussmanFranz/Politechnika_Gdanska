<?php
require_once 'functions.php';
session_start();

if ($_SERVER["REQUEST_METHOD"] === "POST") {

    $db = get_db();

    $query = [
        'login' => $_POST['login'],
    ];

    $user = $db->users->findOne($query);

    if(password_verify($_POST['password'], $user['password']))
    {
        $verify = true;
    }
    else
    {
        $verify = false;
    }

    if ($verify) {
        //echo "Zalogowany!";
        $_SESSION['user'] = $user;
        $_SESSION['login'] = $_POST['login'];
    }
    else
    {
        $_SESSION['login_error'] = true;
    }

    header("Location: index.php");
    exit();
}
?>