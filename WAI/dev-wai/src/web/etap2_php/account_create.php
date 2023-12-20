<?php
include_once './functions.php';
session_start();

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link rel="stylesheet" href="style_php.css">    
</head>
<body>
    <div id="main">
        <form action="create.php" method="POST" id="login_form">
            <table>
                <tr>
                    <td id="login_d">Login: <input type="text" name="login" placeholder="my_login"></td>
                    <td rowspan="4" class="submit_d"><input type="submit" value="Create" class="submit"></td>
                </tr>
                <tr>
                    <td id="password_d">Password: <input type="password" name="password1"> </td>
                </tr>
                <tr>
                    <td id="password_d">Repeat password: <input type="password" name="password2"> </td>
                </tr>
                <tr>
                    <td id="password_d">Email: <input type="text" name="email"> </td>
                </tr>
                <?php
                    if(isset($_SESSION['error']))
                    {
                        $error = $_SESSION['error'];
                        echo '<tr><td id="incorrect" colspan="2">'.$error.'</td></tr>';
                        unset($_SESSION['error']);
                    }
                ?>
            </table>
        </form>
    </div>
</body>
</html>