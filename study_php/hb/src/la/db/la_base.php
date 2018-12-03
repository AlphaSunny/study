<?php

/**
 * @func: 获取la基本信息
 * @return: array
 */

function get_la_base()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM la_base limit 1";
    $db ->query($sql);
    return $db->fetchRow();
}