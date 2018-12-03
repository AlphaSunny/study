<?php



/**
 * @dev:函数：根据ba分配用户地址时的account_id，来查询该用户的充值地址
 * @param $account_id:账号id
 * @return mixed
 */
function get_ba_asset_account_ba_id($account_id)
{
    $db = new DB_COM();
    $sql = "SELECT bit_address FROM ba_asset_account WHERE account_id = '{$account_id}'";
    $db->query($sql);
    $bit_address = $db->getField($sql, 'bit_address');
    return $bit_address;
}

//======================================
// 函数: ba查询地址列表
// 参数: ba_id              用户id
//      page_size          每页数量
//      page_num           偏移量
// 返回: rows               地址数组
//          bit_address     数字货币地址
//          account_id      账号ID
//          ctime           更新时间
//          bind_flag       绑定标志
//          bind_us_id      绑定用户ID
//          utime           创建时间
//======================================
function get_ba_asset_bit_account($ba_id, $page_size, $page_num)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ba_asset_account WHERE ba_id = '{$ba_id}' order by bind_flag asc  limit " . (($page_num) * $page_size) . "," . (($page_num + 1) * $page_size);
    $db->query($sql);
    $rows = $db->fetchAll();
    return $rows;
}