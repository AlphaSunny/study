<?php
/**
 * @param $ca_id
 * @return array
 */
function get_ca_base_info($ca_id)
{
    $db = new DB_COM();
    $sql = "select * from ca_base where ca_id = '$ca_id'";
    $db->query($sql);
    return $db->fetchRow();
}

