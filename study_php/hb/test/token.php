<?php

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");
require_once "../src/inc/common.php";

php_begin();
$args = array("token");
$des = new Des();

chk_empty_args('GET', $args);
$token = get_arg_str('GET', 'token', 128);

$key = Config::TOKEN_KEY;
$decryption_code = $des -> decrypt($token, $key);
$now_time = time();
$code_conf =  explode(',',$decryption_code);

$data = array();
$data['key'] = $key ;
$data['token'] = $code_conf;

$json = json_encode($data);
php_end($json);