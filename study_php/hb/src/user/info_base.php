<?php

require_once "../inc/common.php";
require_once "db/us_base.php";
require_once "db/la_base.php";

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");
/*
 * 功能：获取用户基本信息
 * GET参数：
 *      token
 * 返回：
 * us_id        用户id
 * base_amount
 * lock_amount
 * security_level   用户登记
 * us_level
 * ctime
 *
 */

$args = array('token');
chk_empty_args('GET', $args);

$token = get_arg_str('GET', 'token');

$us_id = check_token($token);

$row = getUsInfoById($us_id);

$row['base_amount'] = $row['base_amount'] / getLaBaseUnit();
$row['lock_amount'] = $row['lock_amount'] / getLaBaseUnit();

//返回的数据
$data = array();
$data['errcode'] = '0';
$data['errmsg'] = '';
$data['rows'] = $row;
$json = json_encode($data);
php_end($json);



