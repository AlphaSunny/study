<?php
header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

require_once ("../../../inc/common.php");

/**
 * @func:获取ba保证金充值和提现记录
 */
php_begin();
$args = array('token');
chk_empty_args('GET', $args);

