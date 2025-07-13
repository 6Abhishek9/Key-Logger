
<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = $_POST['data'] ?? '';
    file_put_contents("received_log.txt", $data, FILE_APPEND);
    echo "OK";
} else {
    echo "Use POST method.";
}
?>
