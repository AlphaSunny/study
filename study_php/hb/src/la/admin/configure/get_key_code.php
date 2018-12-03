<?php
/**
 * Created by PhpStorm.
 * User: Pool
 * Date: 2018/9/6
 * Time: 上午11:18
 */
header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

require_once "../db/la_admin.php";
require_once "../../../inc/common.php";

php_begin();
$args = array('token');
chk_empty_args('GET', $args);
// 用户token
$token = get_arg_str('GET', 'token', 128);
//验证token
$la_id = check_token($token);

$key_code = get_la_by_id($la_id)["key_code"];

$rtn_ary = array();
$rtn_ary['errcode'] = '0';
$rtn_ary['errmsg'] = '';
$rtn_ary['key_code'] = $key_code;
$rtn_str = json_encode($rtn_ary);
php_end($rtn_str);
