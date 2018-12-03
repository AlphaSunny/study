<?php

require_once "../inc/common.php";
require_once "db/la_base.php";
require_once "db/com_base_balance.php";

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

/*
 * 功能：账户变动记录查询
 * GET:
 * token
 * limit
 * offset
 *
 */

php_begin();
$args = array('token');
chk_empty_args('GET', $args);

//用户token
$token = get_arg_str('GET', 'token');
list($limit, $offset) = get_paging_arg('GET');

//验证token
$us_id = check_token($token);

//得到账目总数
$total = getAccountNum($us_id);

//得到
$rows = getAllAccount($us_id, $offset, $limit);

$new_row = array();

foreach ($rows as $row)
{
    $row['tx_amount'] = $row['tx_amount'] / getLaBaseUnit();
    $row['credit_balance'] = $row['credit_balance'] / getLaBaseUnit();
    $new_row[] = $row;
}

$data = array();
$data['errcode'] = '0';
$data['errmsg'] = '';
$data['rows'] = $new_row;
$data['total'] = $total;

$json = json_encode($data);
php_end($json);


