<?php

//======================================
// 函数: 创建登陆记录
// 参数: lgn_data        用户登录数组
// 返回: 0                失败
//      insID            成功
//======================================
function  ins_ca_lgn_login($log_data)
{
    $db = new DB_COM();
    $sql = $db->sqlInsert("ca_log_login", $log_data);
    $q_id = $db->query($sql);
    if ($q_id == 0)
        return 0;
    return $db->insertID();
}


//======================================
// 函数: 获取用户登录前一个hash
// 参数: us_id        用户id
// 返回: prvs_hash    前次登录的hash
//======================================
function  get_pre_hash($us_id)
{
    $db = new DB_COM();
    $sql = "SELECT hash_id FROM ca_log_login WHERE ca_id = '{$us_id}' ORDER BY  ctime DESC LIMIT 1";
    $hash_id = $db->getField($sql, 'hash_id');
    if($hash_id == null)
        return 0;
    return $hash_id;
}