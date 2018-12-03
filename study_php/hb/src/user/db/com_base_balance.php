<?php

/*
 *
 *
 */
function getAccountNum($us_id) {
    $db = new DB_COM();
    $sql = "SELECT hash_id FROM com_base_balance WHERE credit_id = '$us_id'";
    $db->query($sql);
    return $db->affectedRows();

}


/*
 * 函数：根据函数偏移量返回
 */

function getAllAccount($us_id, $offset, $limit)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM com_base_balance WHERE credit_id = '$us_id' order by ctime desc limit $offset, $limit";
    $db ->query($sql);
    return $db->fetchAll();
}
