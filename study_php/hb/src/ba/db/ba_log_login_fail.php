<?php

//======================================
// 函数: 获取ba_log_login_fail基本信息
// 参数: ba_id            用户ba_id
// 返回: row              用户基本信息数组
//         count_error    登录错误次数
//         limt_time      限制时间戳
//======================================

/**
 * @func:根据失败获取ba_id
 * @param $ba_id
 * @return array
 */
function  get_fail_by_ba_id($ba_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ba_log_login_fail WHERE ba_id = '{$ba_id}' order by limt_time DESC limit 1 ";
    $db -> query($sql);
    $row = $db -> fetchRow($sql);
    return $row;
}

//======================================
// 函数: 插入ba_log_login_fail用户基本信息
// 参数: data_base           基本信息数组
//         count_error       登录错误次数
//         limt_time         限制时间戳
// 返回: true           插入成功
// 返回: false          插入失败
//======================================
/**
 * @func: 插入用户失败信息
 * @param $row
 * @return int
 */
function creat_ba_log_login_fail($row)
{
    $db = new DB_COM();
    $sql = $db->sqlInsert("ba_log_login_fail", $row);
    $q_id = $db->query($sql);
    if ($q_id == 0)
        return 0;
    return $db->insertID();
}