<?php

/**
 * @func:根据用户邮箱获取头像
 */

require_once '../inc/config/config.php';

if(empty($_GET['email'])) {
    exit('缺少必要参数');
}

$email = $_GET['email'];

$conn = mysqli_connect(DB_HOST, DB_USER, DB_PASSWORD, DB_NAME);
if(!$conn)
    exit('link to mysql wrong');

$res = mysqli_query($conn, "SELECT avatar FROM users where email = '$email' limit 1");

if(!$res)
    exit('there is no such user');

$row = mysqli_fetch_assoc($res);

echo $row['avatar'];

