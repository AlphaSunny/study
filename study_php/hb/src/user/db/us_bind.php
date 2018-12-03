/**
 * Created by IntelliJ IDEA.
 * User: pool
 * Date: 2018/10/16
 * Time: 下午4:57
 */

<?php

/*
 * 函数：判断该用户是否存在
 */
function get_us_id_by_variable($bind_name, $bind_info)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_bind WHERE bind_name = '$bind_name' and bind_info= '$bind_info' and bind_flag = '1' order by utime DESC limit 1";
    $db->query($sql);
    return $db->fetchRow();
}


function check_pass($us_id, $pass_word_hash, $pass)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_bind WHERE us_id = '$us_id' and bind_name = '$pass' and bind_info='$pass_word_hash' and bind_flag = '1'";
    $db->query($sql);
    return $db->affectedRows();
}