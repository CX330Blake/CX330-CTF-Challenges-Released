<?php
if (!isset($_COOKIE['user_hash'])) {
    header("Location: index.php");
    exit();
}
$user_hash = $_COOKIE['user_hash'];
$basedir = "/var/www/html/log/" . $user_hash;
$logfile = "log/" . $user_hash . "/access.log";

if (!preg_match('/^[a-f0-9]{32}$/', $user_hash)) {
    header("Location: index.php");
    exit();
}

if (!is_dir($basedir)) {
    header("Location: index.php");
    exit();
}

// clear log
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['clear'])) {
    file_put_contents($logfile, '');
    header("Location: dashboard.php");
    exit();
}

// logger
$entry = sprintf(
    '%s - - [%s] "GET %s HTTP/1.1" 200 123 "-" "%s"' . "\n",
    $_SERVER['REMOTE_ADDR'],
    date('d/M/Y:H:i:s O'),
    $_SERVER['REQUEST_URI'],
    $_SERVER['HTTP_USER_AGENT'] ?? ''
);
file_put_contents($logfile, $entry, FILE_APPEND);
?>

<!DOCTYPE html>
<html>

<head>
    <title>LFI-logger</title>

    <style>
        body {
            font-family: 'Noto Sans Mono', monospace;
        }
    </style>
</head>

<body>

    <h1>LFI-logger</h1>


    <?php
    $page = $_GET['page'] ?? 'roses.php';
    $allowed_pages = ['roses.php', 'violets.php', $logfile];
    if (!in_array($page, $allowed_pages, true)) {
        die("Bad Hacker...");
    }

    include($page);
    ?>

    <hr />

    <a href="?page=roses.php">Roses</a>
    <a href="?page=violets.php">Violets</a>
    <a href="?page=log/<?= htmlspecialchars($user_hash) ?>/access.log">View Log</a>
    <form method="POST" style="display: inline;">
        <button type="submit" name="clear">Clear log</button>
    </form>
    <hr />


    <code>

        <?php
        highlight_file(__FILE__);
        ?>
    </code>
</body>

</html>
