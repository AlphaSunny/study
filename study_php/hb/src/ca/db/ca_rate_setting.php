<?php
//======================================
// 函数: 获取ca_rate_setting提现基本信息
// 参数: ca_id                  用户ca_id
// 返回: row                    ca_rate_setting基本信息数组
//         us_level            用户等级要求
//         base_rate           基本汇率
//         min_amount          最小额度
//         max_amount          最大额度
//         bit_type            代理数字货币类型
//         tx_fee              交易手续费率
//         set_time            设定时间戳
//======================================
function  get_ca_settting_withdraw_rate_ca_id($ca_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_rate_setting WHERE  rate_type = '2' and ca_id = '{$ca_id}' limit 1";
    $db -> query($sql);
    $row = $db -> fetchRow();
    return $row;
}

//======================================
// 函数: 获取ca_rate_setting充值基本信息
// 参数: ca_id                  用户ca_id
// 返回: row                    ca_rate_setting基本信息数组
//         us_level            用户等级要求
//         base_rate           基本汇率
//         min_amount          最小额度
//         max_amount          最大额度
//         bit_type            代理数字货币类型
//         tx_fee              交易手续费率
//         set_time            设定时间戳
//======================================
function  get_ca_settting_recharge_rate_ca_id($ca_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_rate_setting WHERE rate_type = '1' and ca_id = '{$ca_id}' limit 1";
    $db -> query($sql);
    $row = $db -> fetchRow();
    return $row;
}