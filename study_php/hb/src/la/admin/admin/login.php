<?php
require_once "../../../inc/common.php";
require_once "../../../plugin/ip_service/get_ip.php";
require_once "../db/la_login_log.php";
require_once "../db/la_admin.php";


header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

ini_set("display_errors", "On");
error_reporting(E_ALL);

/*
 * 功能：admin登陆
 */

php_begin();
$args = array('user', 'password', 'pass_word_hash');
chk_empty_args('GET', $args);

$username = get_arg_str('GET', 'user');
$password = get_arg_str('GET', 'password');
$pass_word_hash = get_arg_str('GET', 'pass_word_hash');

$key = Config::TOKEN_KEY;

//get ip
$ip = get_ip();
//city
$city = getIpInfo($ip);
//time
$login_time = time();
//salt
$salt = rand(10000000, 99999999);

//判断是否超过登陆失败界限
if(getLaLoginFail($username, $login_time)> 3)
    exit_error("108", "you have login fail for too many times, please try later");

$result = log_check($username, $pass_word_hash);

//需记录数据
$login_log = array();
$login_log['user'] = $username;
$login_log['login_time'] = $login_time;
$login_log['login_ip'] = $ip;
$login_log['login_status'] = $result?1:0;
logLogin($login_log);

$la_info = getLaPermission($username);

// 生成token
$timestamp = time() + 2*60*60;
$des = new Des();
$encryption_code = $la_info['user_info']['id'].',' . $timestamp . ',' . $salt;
$token = $des -> encrypt($encryption_code, $key);
//@TODO
login_la_update($username,$ip,$city,$login_time);
// 返回数据做成
$rtn_ary = array();
$rtn_ary['errcode'] = '0';
$rtn_ary['errmsg'] = '';
$rtn_ary['token'] = $token;
$rtn_ary['rows'] = $la_info;
$rtn_str = json_encode($rtn_ary);
php_end($rtn_str);

