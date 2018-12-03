<?php

/*
 * 函数: 获取当前用户最新的一条数据
 * 参数: variable        绑定名
 *        account         账号
 * 返回: row
 */
function getUserBindInfo($variable, $account)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_log_bind WHERE bind_name = '$variable' AND bind_info = '$account' ORDER BY log_id DESC LIMIT 1";
    $db ->query($sql);
    return $db->fetchRow();
}


/*
 *函数: 绑定日志中绑定
 * 函数：data_bind     绑定信息成功数组
 * 返回：true          成功
 *      false         失败
 */
function insUserBind($dataBind)
{
    $dataBind['ctime'] = date("Y-m-d H:i:s");
    $db = new DB_COM();
    $sql = $db->sqlInsert("us_log_bind", $dataBind);
    $res = $db->query($sql);
    if($res == 0)
        return false;
    return true;

}

function checkUserPhoneMsgRestrict($phone)
{
    $day = 86400;
    $timeFlag = time() - $day - 60;
    $db = new DB_COM();
    $sql = "SELECT * FROM us_bind_log WHERE bind_info = '$phone' AND bind_name='phone_code' and limit_time>$timeFlag";
    $db->query($sql);
    return $db->affectedRows();
}