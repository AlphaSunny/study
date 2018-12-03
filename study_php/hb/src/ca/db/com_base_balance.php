<?php

//======================================
// 函数: 获取com_base_balance基本信息
// 参数: ca_id                  用户ca_id
// 返回: row                    用户基本信息数组
//         tx_type              交易类型
//         tx_amount            交易金额
//         credit_balance       借方交易后余额
//         hash_id              HASH值
//         ctime                变动时间
//======================================
function get_log_balance($ca_id)
{
    $db = new DB_COM();
    $sql = "SELECT tx_type,tx_amount,credit_balance,hash_id,ctime FROM com_base_balance WHERE credit_id = '{$ca_id}'";
    $db->query($sql);
    $rows = $db->fetchAll();
    return $rows;
}