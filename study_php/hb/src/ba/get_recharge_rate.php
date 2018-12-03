<?php
header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

require_once "../inc/common.php";
require_once "db/la_base.php";
require_once "db/ba_rate_setting.php";

/**
 * @dev:获取充值汇率
 */

php_begin();
$args = array('token');
chk_empty_args('GET', $args);

$token = get_arg_str('GET', 'token', 150);
$ba_id = check_token($token);

// 通过id获取用户基本信息
$row = get_ba_settting_recharge_rate_ba_id($ba_id);
// 返回数据做成
$rtn_ary = array();
$rtn_ary['errcode'] = '0';
$rtn_ary['errmsg'] = '';
$rtn_ary['ba_id'] = $ba_id;
$rtn_ary['recharge_min_amount'] = floatval($row['min_amount']) * $row['base_rate'] / get_la_base_unit();
$rtn_ary['recharge_max_amount'] = floatval($row['max_amount']) * $row['base_rate'] / get_la_base_unit();
$rtn_ary['recharge_us_level'] = $row['us_level'];
$rtn_ary['recharge_set_time'] = date('Y-m-d H:i', $row['set_time']);
$rtn_ary['recharge_limit_time'] = $row["limit_time"];
$rtn_ary['recharge_bit_type'] = $row['bit_type'];
$rtn_ary['recharge_rate_type'] = "1";
$rtn_ary['recharge_tx_fee'] = $row['tx_fee'];
$rtn_ary['recharge_base_rate'] = floatval($row['base_rate']);

$rtn_str = json_encode($rtn_ary);
php_end($rtn_str);