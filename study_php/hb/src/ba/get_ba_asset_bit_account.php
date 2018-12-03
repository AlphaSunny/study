<?php

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");


require_once "../inc/common.php";
require_once "db/ba_asset_account.php";

php_begin();
$args = array('token');
chk_empty_args('GET', $args);

$token = get_arg_str('GET', 'token', 150);

//当前页
$page_num = get_arg_str('GET', 'offset');
//每页数据量
$page_size = get_arg_str('GET', 'limit');

$ba_id = check_token($token);

//得到查询到的地址
$rows = get_ba_asset_bit_account($ba_id, $page_size?$page_size:10, $page_num);

$new_rows = array();
foreach ($rows as $for_row) {
    $new_row['bit_address'] = $for_row['bit_address'];
    $new_row['account_id'] = $for_row['account_id'];
    $new_row['ctime'] = $for_row['ctime'];
    $new_row['bind_flag'] = $for_row['bind_flag'];
    $new_row['bind_us_id'] = $for_row['bind_us_id'];
    $new_row['utime'] = date("Y-m-d H:i:s",$for_row['utime']);
    $new_rows[] = $new_row;
}

// 返回数据
$rtn_ary = array();
$rtn_ary['errcode'] = '0';
$rtn_ary['errmsg'] = '';
$rtn_ary["ba_id"] = $ba_id;
//总页数
$rtn_ary['page_count'] = count($rows);;
$rtn_ary['rows'] = $new_rows ? $new_rows : [];
$rtn_str = json_encode($rtn_ary);
php_end($rtn_str);

