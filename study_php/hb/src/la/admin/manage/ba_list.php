<?php

require_once "../../../inc/common.php";
require_once "../db/la_admin.php";
require_once "../db/ba_base.php";

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

/**
 * @func:得到用户列表
 */
php_begin();
$args = array('token');
chk_empty_args('GET', $args);

$token = get_arg_str('GET', 'token', 150);
$la_id = check_token($token);

$row = get_la_by_id($la_id);
if(!$row)
    exit_error('112', 'ba 不存在');

$rows = get_ba_list();

$data['errcode'] = '0';
$data['errmsg'] = '';
$data['rows'] = $rows;
$json = json_encode($data);
php_end($json);