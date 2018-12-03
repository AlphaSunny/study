<?php

/**
 * @func:得到用户的基本信息
 */


header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");
require_once "../inc/common.php";
require_once "db/la_base.php";
require_once "db/com_option_config.php";

php_begin();
$args = array('token');
chk_empty_args('GET', $args);

$token = get_arg_str('GET', 'token');
check_token($token);

$row = get_la_base();

if(get_api_key())
    $row['api_key'] = get_api_key()["option_value"];


$data = array();
$data['errcode'] = '0';
$data['errmsg'] = '';
$data['row'] = $row;
$json = json_encode($data);
php_end($json);

