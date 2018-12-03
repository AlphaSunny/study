<?php
/*
 * 函数：根据us_id获取最新登陆失败
 */
function getUserLoginFail($us_id) {
    $db = new DB_COM();
    $sql = "SELECT * FROM us_log_login_fail WHERE us_id ='$us_id' order by limt_time desc limit 1";
    $db->query($sql);
    return $db->fetchRow();
}


/*
 * 函数：得到上一次登陆的hash
 *
 */
function getPreHash($us_id)
{
    $db = new DB_COM();
    $sql = "SELECT hash_id FROM us_log_login WHERE us_id = '{$us_id}' ORDER BY  ctime DESC LIMIT 1";
    $hash_id = $db->getField($sql, 'hash_id');
    if($hash_id == null)
        return 0;
    return $hash_id;
}

/*
 * 函数： 创建新的失败记录
 * $new_fail        失败数据
 * 返回：
 * id               插入id
 */
function create_us_log_login_fail($new_fail)
{
    $db = new DB_COM();
    $sql = $db->sqlInsert('us_log_login_fail', $new_fail);
    $q_id = $db->query($sql);
    if($q_id == 0)
        return 0;
    return $db->insertID();
}

//======================================
// 函数: 登录成功删除所有相关数据
// 参数: us_id          用户id
// 返回: count          删除的行数
//======================================
function delete_us_log_login_fail($us_id)
{
    $db = new DB_COM();
    $sql = "DELETE  FROM us_log_login_fail WHERE us_id = '{$us_id}'";
    $db -> query($sql);
    $count = $db -> affectedRows();
    return $count;
}

//======================================
// 函数: 获取最新登录失败数据
// 参数: us_id        用户id
// 返回: row          登陆失败的最新数据
//======================================
function  get_row_by_us_id($us_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_log_login_fail WHERE us_id = '{$us_id}' order by limt_time DESC limit 1 ";
    $db -> query($sql);
    $row = $db -> fetchRow($sql);
    return $row;
}