<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = trim($_POST['username']);
    $user_hash = md5($username);
    $basedir = "/var/www/html/log/" . $user_hash;

    if (preg_match('/[^a-zA-Z0-9_-]/', $username)) {
        $error = "Username can only contain letters, numbers, dashes, and underscores.";
    } elseif (is_dir($basedir)) {
        $error = "It's used, change it";
    } else {
        mkdir($basedir, 0777, true);
        file_put_contents($basedir . "/access.log", "");

        setcookie("user_hash", $user_hash, time() + 360000, "/"); // 100 hour
        header("Location: dashboard.php");
        exit();
    }
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>LFI Logger - Login</title>
    <style>
        html,
        body {
            height: 100%;
            margin: 0;
            font-family: 'Noto Sans Mono', monospace;
            display: flex;
            justify-content: center;
            align-items: center;
            background-color: #111;
            color: #fff;
        }

        form {
            display: flex;
            flex-direction: column;
            align-items: center;
            background-color: #222;
            padding: 40px;
            border-radius: 12px;
            box-shadow: 0 0 20px rgba(0, 255, 0, 0.2);
        }

        input[type="text"] {
            font-size: 20px;
            padding: 10px;
            margin-bottom: 20px;
            border: none;
            border-radius: 5px;
            width: 300px;
        }

        input[type="submit"] {
            font-size: 18px;
            padding: 10px 20px;
            background-color: #0f0;
            color: #000;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        .error {
            margin-top: 15px;
            color: #f66;
        }
    </style>
</head>

<body>


    <form method="POST">
        <h1>Login</h1>
        <input type="text" name="username" placeholder="Username" required>
        <input type="submit" value="Start">
        <?php if (!empty($error)): ?>
            <div class="error"><?= htmlspecialchars($error) ?></div>
        <?php endif; ?>
    </form>

</body>

</html>
