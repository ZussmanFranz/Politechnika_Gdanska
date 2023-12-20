<?php
use MongoDB\Operation\InsertOne;

require './vendor/autoload.php';


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

function create_user($login, $password, $email)
{
    $db = get_db();

    $new_user = [
        'login' => $login,
        'password' => $password,
        'email' => $email
    ];

    $query = [
        'login' => $login,
        'password' => $password,
        'email' => $email
    ];

    $exists = $db->users->findOne($query); //sprawdza, czy już istnieje

    if ($exists) {
        return 0;
    } else {
        $db->users->insertOne($new_user);
        return 1;
    }
}
