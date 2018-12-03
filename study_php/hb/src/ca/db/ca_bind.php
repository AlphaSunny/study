<?php
//======================================
// 函数: 获取$variable和$acount通过获取最新用户信息
// 参数: account      账号
//      variable     绑定name
// 返回: row          最新信息数组
//======================================
function get_ca_id_by_variable($variable , $account)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_bind WHERE bind_name = '{$variable}' AND bind_info = '{$account}' ORDER BY utime DESC LIMIT 1 ";
    $db -> query($sql);
    $row = $db -> fetchRow();
    return $row;
}


//======================================
// 函数: 检测密码是否正确
// 参数: pass_word_hash       密码HASH
//       us_id                用户id
// 返回: count                影响的行数
//======================================
function check_pass($ca_id,$pass_word_hash,$variable)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_bind WHERE ca_id = '{$ca_id}' AND bind_info = '{$pass_word_hash}' AND bind_name = '{$variable}'";
    $db -> query($sql);
    $count = $db -> affectedRows();
    return $count;
}

function get_ca_bind_info_by_id($ca_id)
{
    $db = new DB_COM();
    $sql = "select * from ca_bind where ca_id = '{$ca_id}' and bind_flag = 1";
    $db -> query($sql);
    return $db->fetchAll();
}