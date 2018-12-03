<?php

require_once ("../inc/common.php");
require_once ("db/us_bind.php");
require_once ("db/us_log_login_fail.php");
require_once ("db/us_log_login.php");
require_once ("db/us_log_bind.php");
require_once ("../plugin/ip_service/get_ip.php");

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

/*
 * 功能：用户登陆
 * 参数：
 * country_code     国家代码
 * phone            电话好码
 * hash             密码哈希
 * cfm_code         验证码
 *
 * 返回：
 *      result
 *      token
 *
 */

php_begin();
$args = array('country_code', 'cellphone', 'pass_word_hash');
chk_empty_args('GET', $args);

$key = Config::TOKEN_KEY;
//国家代码
$country_code = get_arg_str('GET', 'country_code');
//电话好码
$cellphone = get_arg_str('GET', 'cellphone');
//密码hash
$pass_word_hash = get_arg_str('GET', 'pass_word_hash');

//严格电话号码
$phone_strict = $country_code.'-'.$cellphone;

//nonce
$salt = rand(2000000, 9000000);

//时间
$currentTime = time();
$expireTime = time() + 2*60*60;

$bind_name = 'cellphone';
$pass = 'password_login';


//判断该用户是否存在
$row = get_us_id_by_variable($bind_name, $phone_strict);
$us_id = $row['us_id'];

if(empty($row['us_id'])||$row['bind_flag'] == '9'){
    exit_error('112', 'this phone is not registered');
}
if($row['bind_flag'] == '2')
    exit_error('118', 'this account is rejected');
if($row['bind_flag'] == '3')
    exit_error('137', 'this account is refused');

//获取最新登陆失败信息
$fail = getUserLoginFail($row['us_id']);
if($fail)
{
    $count = $fail['count_error'];
    $limt_time = $fail['limt_time'];
    if($limt_time > $expireTime) {
        exit_error('122', $limt_time>$expireTime);
    }
}

//验证密码
$check = checkPass($us_id, $pass_word_hash, $pass);
if(!$check) {
    if(!$fail)
    {
        $new_fail = $fail;
        $new_fail['count_error'] = $fail['count_error'] + 1;
        $new_fail['limt_time'] = $expireTime + pow(2, $new_fail['count_error']);
        unset($new_fail['log_id']);
        $result = createUserLoginFail($new_fail);
        exit_error('116', pow(2, $new_fail['count_error']));

    } else
    {
        $new_fail['us_id'] = $us_id;
        $new_fail['us_ip'] = get_int_ip(get_ip());
        $new_fail['lgn_type'] ='phone_code';
        $new_fail['count_error'] = 1;
        $new_fail['limt_time'] = $expireTime + pow(2, $new_fail['count_error']);
        $new_fail['ctime'] = date("Y-m-d H:i:s");
        $result = createUserLoginFail($new_fail);
        exit_error("116", pow(2, $new_fail['count_error']));
    }
}

$des = new Des();
$toEncrypt = $us_id.','.$expireTime.','.$salt;
$token = $des-> encrypt($toEncrypt, $key);
//记录参数
$lgn_type = "phone";
$us_ip = get_ip();
$ip_area = getIpInfo($us_ip);
$utime = time();
$ctime = date("Y-m-d H:i:s");
// 创建登录记录
$log_data = array();
$log_data['prvs_hash'] = getPreHash($row['us_id']);
$log_data['hash_id'] = hash('md5',$row['us_id'] . $lgn_type . $us_ip .  $utime . $ctime .$salt);
$log_data['lgn_type'] = $lgn_type;
$log_data['us_ip'] = ip2long($us_ip);
$log_data['us_id'] = $row['us_id'];
$log_data['ip_area'] = $ip_area;
$log_data['utime'] = $utime;
$log_data['ctime'] = $ctime;
// 写入登录数据
$ret = insUserLogin($log_data);
// 返回数据做成
$rtn_ary = array();
$rtn_ary['errcode'] = '0';
$rtn_ary['errmsg'] = '';
$rtn_ary['token'] = $token;
$rtn_str = json_encode($rtn_ary);
php_end($rtn_str);
