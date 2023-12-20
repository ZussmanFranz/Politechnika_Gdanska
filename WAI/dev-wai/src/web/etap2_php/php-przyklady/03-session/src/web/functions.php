<?php

require '../../vendor/autoload.php';


function get_db()
{
    $mongo = new MongoDB\Client(
        "mongodb://localhost:27017/wai",
        [
            'username' => 'wai_web',
            'password' => 'w@i_w3b',
        ]);

    $db = $mongo->wai;

    return $db;
}

function &get_cart()
{
    if (!isset($_SESSION['cart'])) {
        $_SESSION['cart'] = []; //pusty koszyk
    }

    return $_SESSION['cart'];
}

function clear_cart()
{
    if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['clear_cart'])) {
        $_SESSION['cart'] = [];

        header('Location: ' . $_SERVER['HTTP_REFERER']);
        exit;
    }
}

