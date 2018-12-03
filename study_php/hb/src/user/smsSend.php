<?php
/**
 * Created by IntelliJ IDEA.
 * User: pool
 * Date: 2018/10/16
 * Time: 下午1:40
 */

require_once "../inc/common.php";
require_once "../inc/judge_format.php";
require_once "db/us_log_bind.php";

header("cache-control:no-cache,must-revalidate");
header("Content-Type:application/json;charset=utf-8");

/*
 * 功能：发送手机验证码
 * GET：
 *      cellphone:          手机号码
 *      country_code:       国家代码
 *
 */

if(!isset($_SESSION)) {
    session_start();
}

php_begin();
$args = array('cellphone', 'country_code', 'bind_type');
chk_empty_args('GET',$args);

$cellphone = get_arg_str('GET','cellphone',20);
$country_code = get_arg_str('GET','country_code', 10);
$bind_type = get_arg_str('GET','bind_type', 20);
$cfm_code = get_arg_str('GET','cfm_code', 50);
$token = get_arg_str('GET','token', 128);
$code = rand(100000, 999999);
$phoneStrict = $country_code.'_'.$cellphone;

if(isPhone($phone)) {
    exit_error("100", "phone format error");
}
if($cfm_code != $_SESSION['authcode'])
    exit_error("135", "authcode is not right");

$phoneSmsNum = checkUserPhoneMsgRestrict($phoneStrict);

if($phoneSmsNum > 40) {
    exit_error('108', 'over the restrict of send sms');
}

$lastBind = getUserBindInfo('phone_code', $phoneStrict);
if($lastBind['limit_time'] < time())
    exit_error('116', 'the sms has expired');


require_once "db/la_admin.php";
require_once "../inc/common_agent_sms_service.php";

$key_code = getLaInfo()['key_code'];
$smsReturn = send_sms_by_agent_service($cellphone, $code, $key_code);

//sms发送录入数据库
if($smsReturn["errcode"] = '0')
{
    $time_limit = time() + 60;
    $data = array();
    $data['us_id'] = get_guid();
    $data['bind_type'] = $bind_type;
    $data['bind_name'] = 'phone_code';
    $data['bind_info'] = $phoneStrict;
    $data['bind_salt'] = $code;
    $data['count_error'] = 0;
    $data['limit_time'] = $time_limit;
    $res = insUserBind($data);
    exit_ok();
}
else
{
    exit_error('124', "send error");
}

