<?php

require_once "../../../inc/common.php";
require_once "../db/la_admin.php";
require_once '../db/us_base.php';
require_once "../db/la_base.php";
require_once "../db/ca_base.php";
require_once "../db/ba_base.php";
require_once "../db/us_ba_recharge_request.php";
require_once "../db/us_ba_withdraw_request.php";
require_once "../db/us_ca_recharge_request.php";
require_once "../db/us_ca_withdraw_request.php";
header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");


php_begin();
$args = array("token");
chk_empty_args('GET', $args);

//获得token
$token = get_arg_str('GET', 'token', 150);
$begin_limit_time = get_arg_str('GET', 'begin_limit_time');
$end_limit_time = get_arg_str('GET', 'end_limit_time');
$la_id = check_token($token);


$row = get_la_by_id($la_id);
if(!$row)
{
    exit_error('112', '用户不存在');
}

$rows = array();

//得到基本单位
$unit = get_la_base_unit()['unit'];

//user的总账
$row = get_us_sum_amount_info();
$rows["sum_us_base_amount"] =  $row['sum(base_amount)'] / $unit;
$rows["sum_us_lock_amount"] =  $row['sum(lock_amount)'] / $unit;

//ba的总账
$row = get_ba_sum_amount_info();
$rows["sum_ba_base_amount"] =  $row['sum(base_amount)'] / $unit;
$rows["sum_ba_lock_amount"] =  $row['sum(lock_amount)'] / $unit;

//ca的总账
$row = get_ca_sum_amount_info();
$rows["sum_ca_base_amount"] =  $row['sum(base_amount)'] / $unit;
$rows["sum_ca_lock_amount"] =  $row['sum(lock_amount)'] / $unit;

//得到ba的充值和提取总账
$rows["sum_ba_recharge_base_amount"] = get_ba_sum_us_ba_recharge_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit;
$rows["sum_ba_withdraw_base_amount"] = get_ba_sum_us_ba_withdraw_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit;

//得到ca的充值和提取总账
$rows["sum_ca_recharge_base_amount"] = get_ca_sum_us_ca_recharge_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit;
$rows["sum_ca_withdraw_base_amount"] = get_ca_sum_us_ca_withdraw_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit;

//得到用户的充值和提取总账
$rows["sum_us_recharge_base_amount"] = get_ba_sum_us_ba_recharge_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit + get_ca_sum_us_ca_recharge_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit;
$rows["sum_us_withdraw_base_amount"] = get_ba_sum_us_ba_withdraw_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit + get_ca_sum_us_ca_withdraw_request_info($begin_limit_time,$end_limit_time)["sum(base_amount)"] / $unit;

//统计ba，user，la注册数
$rows["ba_register_count"] = get_ba_sum_register_amount_info($begin_limit_time,$end_limit_time)["count(*)"];
$rows["us_register_count"] = get_us_sum_register_amount_info($begin_limit_time,$end_limit_time)["count(*)"];
$rows["ca_register_count"] = get_ca_sum_register_amount_info($begin_limit_time,$end_limit_time)["count(*)"];


//邀请总数


$data = array();
$data['errcode'] = '0';
$data['errmsg'] = '';
$data['rows'] = $rows;
$json = json_encode($data);
php_end($json);


