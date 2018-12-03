<?php
//获取身份证姓名
function get_ca_log_bind_info_for_idName($ca_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_log_bind WHERE bind_type = 'text' AND bind_name = 'name' AND ca_id = '{$ca_id}' AND count_error != '2' ORDER BY log_id DESC LIMIT 1 ";
    $db->query($sql);
    $row =$db -> fetchRow();
    return $row;
}
//获取身份证图片
function get_ca_log_bind_info_for_idPhoto($ca_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_log_bind WHERE bind_type = 'file' AND bind_name = 'idPhoto' AND ca_id = '{$ca_id}' AND count_error != '2' ORDER BY log_id DESC LIMIT 1 ";
    $db->query($sql);
    $row = $db -> fetchRow();
    return $row;
}
//获取身份证号
function get_ca_log_bind_info_for_idNum($ca_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_log_bind WHERE bind_type = 'text' AND bind_name = 'idNum' AND ca_id = '{$ca_id}' AND count_error != '2' ORDER BY log_id DESC LIMIT 1 ";
    $db->query($sql);
    $row = $db -> fetchRow();
    return $row;
}