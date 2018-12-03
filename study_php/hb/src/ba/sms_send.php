<?php
header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

require_once ("../inc/common.php");
require_once ("../inc/judge_format.php");
require_once ("db/ba_log_bind.php");
/*
 * 功能：发送手机验证码
 * GET：
 *      cellphone:          手机号码
 *      country_code:       国家代码
 *
 */
php_begin();
if(!isset($_SESSION)) {
    session_start();
}

$args = array('cellphone', 'country_code', 'bind_type');
chk_empty_args('GET',$args);

$cellphone = get_arg_str('GET','cellphone',20);
$country_code = get_arg_str('GET','country_code', 10);
$bind_type = get_arg_str('GET','bind_type', 20);
$cfm_code = get_arg_str('GET','cfm_code', 50);
$token = get_arg_str('GET','token', 128);
$code = rand(100000, 999999);
$phone_strict = $country_code.'-'.$cellphone;

if(!isPhone($cellphone)) {
    exit_error("100", "phone format error");
}
if($cfm_code != $_SESSION['authcode'])
    exit_error("135", "authcode is not right");

$phone_code_num_limit = ba_phone_code_limit_check($phone_strict);

if($phone_code_num_limit>40)
    exit_error('108','no times for send code');

//获取最新一条发送记录
$phone_code_last_time = get_ba_log_bind_by_variable('phone_code',$phone_strict);

//判断是否在限制时间范围内
if($phone_code_last_time['limt_time'] > time())
    exit_error('116',$phone_code_last_time['limt_time'] - time());


require_once "db/la_admin.php";
require_once "../inc/common_agent_sms_service.php";
$key_code = get_la_admin_info()["key_code"];
$output_array = send_sms_by_agent_service($cellphone,$code,$key_code);
// 验证发送短信(SendSms)接口
if($output_array["errcode"] == "0"){
    $time_limit = time() + 60 ;
    $data = array();
    $data['ba_id']  = get_guid();
    $data['bind_name']  = 'phone_code';
    $data['bind_info']  = $phone_strict;
    $data['count_error'] = 0;
    $data['limt_time']  = $time_limit;
    $data['bind_type']  = $bind_type;
    $data['bind_salt']  = $code;
    $res = ins_ba_verification_code($data);
    exit_ok();
}else{
    exit_error('124','发送失败,请稍后再试');
}