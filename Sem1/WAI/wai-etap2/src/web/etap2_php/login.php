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
        <form action="zaloguj.php" method="POST" id="login_form">
            <table>
                <tr>
                    <td id="login_d">Login: <input type="text" name="login" placeholder="my login"></td>
                    <td rowspan="2" id="submit_d"><input type="submit" value="Log in" id="submit"></td>
                </tr>
                <tr>
                    <td id="password_d">Password: <input type="password" name="password"> </td>
                </tr>
            </table>
        </form>
    </div>
</body>
</html>