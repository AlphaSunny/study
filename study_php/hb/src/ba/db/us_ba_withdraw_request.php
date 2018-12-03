<?php
/**
 * @param $ba_id
 * @return array
 */
function get_us_ba_withdraw_count($ba_id)
{
    $db = new DB_COM();
    $sql = "select count(*) from us_ba_withdraw_request where ba_id = '$ba_id' and qa_flag=0";
    $db->query($sql);
    return $db->fetchRow();
}

//======================================
// 函数: 根据状态，获取us_ba_withdraw_request基本信息
// 参数: ba_id                      用户ba_id
//      qa_flag                    订单状态
// 返回: row                        基本信息数组
//         asset_id                 充值资产ID
//         bit_amount               数字货币金额
//         base_amount              充值资产金额
//         tx_time                  请求时间戳
//         tx_hash                  交易HASH
//         us_id                    用户ID
//         qa_id                    请求ID
//         ba_id                    代理商ID
//         tx_detail                交易明细（JSON）
//         ba_account_id            代理商账号ID（Hash）
//======================================
function  get_ba_withdraw_request_ba_id($ba_id,$qa_flag)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_ba_withdraw_request WHERE ba_id = '{$ba_id}' and qa_flag = '{$qa_flag}'";
    $db -> query($sql);
    $rows = $db -> fetchAll();
    return $rows;
}


//======================================
// 函数: 下载ba充值请求的列表
// 参数: ba_id                      ba用户id
// 返回: rows                       数量
//======================================
function  get_ba_withdraw_request_download_ba_id($ba_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_ba_withdraw_request WHERE  qa_flag = '0' and ba_id = '{$ba_id}'";
    $db -> query($sql);
    $rows = $db -> fetchAll();
    return $rows;
}