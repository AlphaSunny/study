<?php

require_once "../../../inc/common.php";
require_once "../db/la_admin.php";
require_once "../db/com_option_config.php";


header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");


/**
 * @func:注册功能开关
 * @GET:token
 *      type
 *      status:修改到的目标状态
 * @RETURN:
 */

php_begin();
$args = array('token', 'type');
chk_empty_args('GET', $args);

$token = get_arg_str('GET', 'token', 128);
$type = get_arg_str('GET', 'type', 10);
$status = get_arg_str('GET', 'status', 10);

if($status!=0&&$status!=1)
    exit_error('100', 'status error');

$la_id = check_token($token);

$row = get_la_by_id($la_id);
if(!$row)
    exit_error('112', 'user is not existed');

$res = reg_permission_modify($type, $status);
if($res)
    exit_ok();
exit_error('101', '修改注册权限失败');