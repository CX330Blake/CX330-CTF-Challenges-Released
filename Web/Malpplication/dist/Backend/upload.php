<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET,POST,OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['file'])) {
    header("Access-Control-Allow-Origin: *"); // Bug0: Dangerous 
    header("Access-Control-Allow-Methods: POST, OPTIONS");
    header("Access-Control-Allow-Headers: Content-Type");
    $upload_dir = __DIR__ . '/uploads/';
    if (!file_exists($upload_dir)) {
        if (!mkdir($upload_dir, 0777, true)) {
            die("❌ Failed to create directory: " . error_get_last()['message']);
        }
    }

    $file_name = $_FILES['file']['name'];
    $extension = pathinfo($_FILES['file']['name'], PATHINFO_EXTENSION);
    $file_tmp = $_FILES['file']['tmp_name'];

    if (str_ends_with($file_name, ".php")) {
        echo json_encode(["status" => "failed", "message" => "❌ Bad hacker..."]);
        die;
    }

    $file_name = md5(uniqid(rand(), true)) . '.' . $extension;


    // Bug1: Arbitrary file upload, no extension sanitization 
    $upload_path = $upload_dir . $file_name;

    // Bug2: Didn't check the MIME-Type, attackers can fake the Content-Type
    // Bug3: Didn't check the file content, attackers can upload webshells
    if (move_uploaded_file($file_tmp, $upload_path)) {
        echo json_encode(["status" => "success", "message" => "http://" . $_SERVER['HTTP_HOST'] . "/uploads/" . $file_name]);
        exit();
    } else {
        echo json_encode(["status" => "failed", "message" => "❌ Upload Failed"]);
        exit();
    }
} else {
    echo json_encode(["status" => "failed", "message" => "❌ no file uploaded"]);
}
