<?php
/**
 * @func:得到用户最近的注册
 * @param $variable
 * @param $account
 * @return array
 */
function get_ba_id_by_variable($variable , $account)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ba_bind WHERE bind_name = '{$variable}' AND bind_info = '{$account}' ORDER BY utime DESC LIMIT 1 ";
    $db -> query($sql);
    $row = $db -> fetchRow();
    return $row;
}


//======================================
// 函数: 创建用户绑定信息
// 参数: data_bind          绑定信息数组
// 返回： true              成功
//       false             失败
//======================================
function ins_bind_ba_reg_bind_info($data_bind)
{
    $data_bind['utime'] = time();
    $data_bind['ctime'] = date("Y-m-d H:i:s");
    $db = new DB_COM();
    $sql = $db->sqlInsert("ba_bind", $data_bind);
    $q_id = $db->query($sql);
    if ($q_id == 0)
        return false;
    return true;
}

/**
 * @func:检查密码是否正确
 * @param $ba_id
 * @param $pass_word_hash
 * @param $variable
 * @return int
 */
function check_pass($ba_id,$pass_word_hash,$variable)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ba_bind WHERE ba_id = '{$ba_id}' AND bind_info = '{$pass_word_hash}' AND bind_name = '{$variable}'";
    $db -> query($sql);
    $count = $db -> affectedRows();
    return $count;
}


/**
 * @func：获取用户绑定信息
 * @param $ba_id:用户id
 * @return array
 */
function  get_ba_bind_info_by_id($ba_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ba_bind WHERE ba_id = '{$ba_id}' AND bind_flag = 1";
    $db->query($sql);
    $row = $db ->fetchAll();
    return $row;
}