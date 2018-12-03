<?php

/**
 * @return array
 */
function get_ca_list()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM ca_base";
    $db->query($sql);
    return $db->fetchAll();
}

/**
 * @func: 得到用户的总账
 * @return array
 */

/**
 * @func: 得到用户的总账
 * @return array
 */
function get_ca_sum_amount_info()
{
    $db = new DB_COM();
    $sql = "SELECT sum(base_amount), sum(lock_amount) FROM ca_base";
    $db->query($sql);
    $row = $db->fetchRow();
    return $row;
}

/**
 * @func: 取得ca所有的注册数
 * @param $begin_limit_time
 * @param $end_limit_time
 * @return array
 */
function get_ca_sum_register_amount_info($begin_limit_time,$end_limit_time)
{
    $where ='';
    if($begin_limit_time){
        $where .= "tx_time >= '{$begin_limit_time}'";
    }
    if($end_limit_time){
        if($where){
            $where .= "AND tx_time <= '{$end_limit_time}'";
        }else{
            $where .= "tx_time <= '{$end_limit_time}'";
        }
    }
    if($where){
        $sql = "SELECT count(*) FROM ba_base where '{$where}'";
    }else{
        $sql = "SELECT count(*) FROM ba_base ";
    }
    $db = new DB_COM();
    $db->query($sql);
    $row = $db->fetchRow();
    return $row;
}