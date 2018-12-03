<?php

function get_ca_recharge_amount_request_ca_id($ca_id)
{
    $db = new DB_COM();
    $sql = "select count(*) from us_ca_recharge_request where ca_id = '$ca_id' and qa_flag = 0";
    $db->query($sql);
    return $db->fetchRow();
}


function get_ca_recharge_request_ca_id($ca_id, $qa_flag)
{
    $db = new DB_COM();
    $sql = "select * from us_ca_recharge_request where ca_id = '$ca_id' and qa_flag = '$qa_flag'";
    $db->query($sql);
    return $db->fetchAll();
}