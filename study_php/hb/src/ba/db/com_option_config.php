<?php

function get_ba_bit_type()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM com_option_config WHERE option_name = 'bit_type' and status = 1";
    $db->query($sql);
    $rows = $db->fetchAll();
    return $rows;
}

/**
 * @func:判断该种数字货币代理商类型是否开放注册
 * @param $bit_type:需注册的ba类型
 * @return array
 */
function bit_type_exist_or_not($bit_type){
    $db = new DB_COM();
    $sql = "SELECT * FROM com_option_config WHERE option_name = 'bit_type' and option_key = '{$bit_type}'";
    $db->query($sql);
    $row = $db->fetchRow();
    return $row;
}

/**
 * @func:判断la是否已经开放数字货币代理商的注册
 * @return array
 */
function ba_can_reg_or_not(){
    $db = new DB_COM();
    $sql = "SELECT * FROM com_option_config WHERE option_name = 'ba_lock' limit 1";
    $db->query($sql);
    $row = $db->fetchRow();
    return $row;
}