<?php
/**
 * Created by IntelliJ IDEA.
 * User: pool
 * Date: 2018/10/16
 * Time: 上午11:00
 */

require_once "../../../inc/common.php";
require_once "../db/com_option_config.php";

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

/*
 * DEV: get if the register is locked
 */

php_begin();
$args = array('type');
chk_empty_args('GET', $args);


$type = get_arg_str('GET', 'type', 255);
$res = getRegPermission($type);

// return json
$data = array();
$data['errcode'] = 0;
$data['errmsg'] = '';
$data['row'] = $res;
$json = json_encode($data);
php_end($json);