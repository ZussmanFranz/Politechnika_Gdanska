<?php
    session_start();

    if(isset($_SESSION['user']))
    {
        header("Location: index.php");
        exit();
    }

    if(isset($_SESSION['login'])){
        $login = $_SESSION['login'];
    }
    else
    {
        $login = "";
    }
    
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
        <form action="login.php" method="POST" id="login_form">
            <table>
                <tr>
                    <td id="login_d">Login: <input type="text" name="login" placeholder="my_login" value <?= $login?>></td>
                    <td rowspan="2" class="submit_d"><input type="submit" value="Log in" class="submit"></td>
                </tr>
                <tr>
                    <td id="password_d">Password: <input type="password" name="password"> </td>
                </tr>
                <?php
                if((!isset($_SESSION['user'])) && (isset($_SESSION['login_error'])))
                {
                    echo '<tr><td colspan="2" id="incorrect">Incorrect login or password!</td></tr>';
                    unset($_SESSION['login_error']);
                }
                ?>
            </table>
        </form>
        <form action="account_create.php" method="POST" id="create_form">
            <table>
                <tr>
                    <td class="submit_d"><input type="submit" value="Create new account" class="submit" id="create_subm"></td>
                </tr>
            </table>
        </form>
    </div>
</body>
</html>