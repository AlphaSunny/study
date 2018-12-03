<?php

/*
 * 函数：根据用户id获取用户信息
 * 参数：
 * us_id    用户id
 *
 */
function getUsInfoById($us_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_base WHERE us_id = '$us_id'";
    $db->query($sql);
    return $db->fetchRow();
}

