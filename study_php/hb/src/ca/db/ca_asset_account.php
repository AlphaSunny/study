<?php


//======================================
// 函数: 根绝id，查询地址
// 参数: account_id                账号ID
// 返回: bit_address               地址
//======================================
function get_ca_asset_account_ca_id($account_id)
{
    $db = new DB_COM();
    $sql = "SELECT lgl_address FROM ca_asset_account WHERE account_id = '{$account_id}'";
    $db->query($sql);
    $bit_address = $db->getField($sql, 'lgl_address');
    return $bit_address;
}


//======================================
// 函数: 获取ca渠道列表
// 参数:
// 返回: rows              渠道列表数组信息
//======================================
function  ca_get_distinct_ca_channel_list()
{
    $db = new DB_COM();
    //充值信息存在，返回原先的地址
    $sql = "SELECT distinct ca_channel FROM ca_asset_account";
    $db -> query($sql);
    $rows = $db -> fetchAll();
    return $rows;
}


function ca_get_asset_account_info($ca_id)
{
    $db = new DB_COM();
    $sql = "select * from ca_asset_account where ca_id ='$ca_id'";
    $db->query($sql);
    return $db->fetchAll();
}
