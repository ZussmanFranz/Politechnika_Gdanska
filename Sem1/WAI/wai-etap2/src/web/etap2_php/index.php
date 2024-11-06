<?php

if ($_SERVER['REQUEST_METHOD'] === 'GET')
{
    header("Location: login.php");
    exit;
}

$login = $_POST['login'];
$password = $_POST['password'];

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
    <div>
        <section>
            <div class="gallery_detailed" id="Empire">
                <img src="./img/Empire1.jpg" alt="First Thousand Sons image">
                <img src="./img/Empire2.jpg" alt="First Thousand Sons image">
                <img src="./img/Empire3.jpg" alt="First Thousand Sons image">
                <img src="./img/Empire4.jpg" alt="First Thousand Sons image">
            </div>
        </section>
        <section>
            <div class="gallery_detailed" id="Blood_Rage">
                <img src="./img/BloodRage1.jpg" alt="First Thousand Sons image">
                <img src="./img/BloodRage2.jpg" alt="First Thousand Sons image">
                <img src="./img/BloodRage3.jpg" alt="First Thousand Sons image">
                <img src="./img/BloodRage4.jpg" alt="First Thousand Sons image">
            </div>
        </section>
        <section>
            <div class="gallery_detailed" id="Drukhari">
                <img src="./img/Eldar1.jpg" alt="First Thousand Sons image">
                <img src="./img/Eldar2.jpg" alt="First Thousand Sons image">
                <img src="./img/Eldar3.jpg" alt="First Thousand Sons image">
                <img src="./img/Eldar4.jpg" alt="First Thousand Sons image">
            </div>
        </section>
        <section>
            <div class="gallery_detailed" id="Thousand_Sons">
                <img src="./img/ThousandSons1.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons2.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons3.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons4.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons4.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons4.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons4.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons4.jpg" alt="First Thousand Sons image">
                <img src="./img/ThousandSons4.jpg" alt="First Thousand Sons image">
            </div>
        </section>
    </div>
    <div id="skull"><a href="#header"><img src="./img/servo-skull.svg" alt="Go to top"></a></div>
    <footer id="footer">Yauheni Pyryeu, 023.M3</footer>
</div>

</body>
</html>