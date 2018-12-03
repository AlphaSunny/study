<?php

/*
 * 函数：得到la的基准单位
 * 参数：none
 * 返回：
 * uint ：la的基准单位
 */
function getLaBaseUnit() {
    $db = new DB_COM();
    $sql = "SELECT unit FROM la_base limit 1";
    $db->query($sql);
    return $db->fetchRow()['unit'];
}