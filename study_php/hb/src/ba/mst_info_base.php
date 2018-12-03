<?php

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

require_once ("../inc/common.php");
require_once 'db/ba_base.php';
require_once 'db/us_ba_recharge_request.php';
require_once 'db/us_ba_withdraw_request.php';
require_once 'db/ba_rate_setting.php';
require_once 'db/la_base.php';
require_once 'db/base_withdraw_request.php';
require_once 'db/base_recharge_request.php';


/**
 * @功能：获取ba基本信息
 */

php_begin();
$args = array('token');
chk_empty_args('GET', $args);

//验证token
$token = get_arg_str('GET', 'token', 128);
$ba_id = check_token($token);


//获得ba基本基本信息
$row = get_ba_base_info($ba_id);

$count_recharge = get_us_ba_recharge_count($ba_id);
$count_withdraw = get_us_ba_withdraw_count($ba_id);


//if($row["ba_type"])
//{
//    $count_base_recharge = get_base_recharge_amount_request_ba_id($ba_id);
//    $count_base_withdraw = get_base_withdraw_amount_request_ba_id($ba_id);
//}

// 给前端返回的数据
$rtn_ary = array();
$rtn_ary['errcode'] = '0';
$rtn_ary['errmsg'] = '';
$rtn_ary['ba_id'] =$ba_id;
$rtn_ary['base_amount'] = $row["base_amount"] / get_la_base_unit();
$rtn_ary['ba_account'] = $row["ba_account"];
$rtn_ary['lock_amount'] =$row["lock_amount"] / get_la_base_unit();
$rtn_ary['security_level'] =$row["security_level"];
$rtn_ary['bit_type'] = $row["ba_type"];
$rtn_ary['ba_level'] = $row["ba_level"];
$rtn_ary['count_recharge'] = $count_recharge["count(*)"];
$rtn_ary['count_withdraw'] = $count_withdraw["count(*)"];
//$rtn_ary['count_base_recharge'] = $count_base_recharge["count(*)"];
//$rtn_ary['count_base_withdraw'] = $count_base_withdraw["count(*)"];

$rtn_ary['recharge_rate'] = floatval(get_ba_settting_recharge_rate_ba_id($ba_id)["base_rate"]);
$rtn_ary['withdraw_rate'] = floatval(get_ba_settting_withdraw_rate_ba_id($ba_id)["base_rate"]);
$rtn_str = json_encode($rtn_ary);
php_end($rtn_str);
