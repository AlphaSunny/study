<?php


function get_ca_withdraw_amount_request_ca_id($ca_id)
{
    $db = new DB_COM();
    $sql = "select count(*) from us_ca_withdraw_request where ca_id = '$ca_id' and qa_flag = 0";
    $db->query($sql);
    return $db->fetchRow();
}


//======================================
// 函数: 根据状态，获取us_ca_withdraw_request基本信息
// 参数: ca_id                      用户ca_id
//      qa_flag                    订单状态
// 返回: row                        基本信息数组
//         asset_id                 充值资产ID
//         bit_amount               数字货币金额
//         base_amount              充值资产金额
//         tx_time                  请求时间戳
//         tx_hash                  交易HASH
//         us_id                    用户ID
//         qa_id                    请求ID
//         ca_id                    代理商ID
//         tx_detail                交易明细（JSON）
//         ca_account_id            代理商账号ID（Hash）
//======================================
function  get_ca_withdraw_request_ca_id($ca_id,$qa_flag)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_ca_withdraw_request WHERE ca_id = '{$ca_id}' and qa_flag = '{$qa_flag}'";
    $db -> query($sql);
    $rows = $db -> fetchAll();
    return $rows;
}