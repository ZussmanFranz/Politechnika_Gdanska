<?php
require_once 'functions.php';
session_start();

if($_POST['login'] == "")
{
    $_SESSION['error'] = "please, enter login";
    header("Location: account_create.php");
    exit();
}
else if(((!isset($_POST['password1'])) || (!isset($_POST['password2']))) && (!isset($_SESSION)))
{
    $_SESSION['error'] = "please, enter both passwords";
    header("Location: account_create.php");
    exit();
}
else if(($_POST['email'] == "") && (!isset($_SESSION)))
{
    $_SESSION['error'] = "please, enter email";
    header("Location: account_create.php");
    exit();
}

if((($_POST['password1'] == $_POST['password2']) && (!isset($_SESSION['error']))))
{
    $password_hashed = password_hash($_POST['password1'], PASSWORD_DEFAULT);
    create_user($_POST['login'], $password_hashed, $_POST['email']);
    $_SESSION['login'] = $_POST['login'];
    $_SERVER['REQUEST_METHOD'] = 'POST';
    header("Location: account.php");
    exit();
}
else{
    $_SESSION['error'] = "passwords should be the same";
    header("Location: account_create.php");
}

?>