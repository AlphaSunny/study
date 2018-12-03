<?php

/**
 * func：得到la的api秘钥
 */

function get_api_key()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM com_option_config WHERE option_name = 'api_key'";
    $db->query($sql);
    return $db ->fetchRow();
}