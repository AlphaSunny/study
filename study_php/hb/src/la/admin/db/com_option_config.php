<?php
/**
 * @param $type:修改的ba,ca,还是user
 * @param $status:修改的目标状态
 * @return int
 */
function reg_permission_modify($type, $status)
{
    $db = new DB_COM();
    $sql = '';
    switch ($type) {
        case 'ba':
            $sql = "update com_option_config set option_value = '$status' where option_name = 'ba_lock' ";
            break;
        case 'ca':
            $sql = "update com_option_config set option_value = '$status' where option_name = 'ca_lock' ";
            break;
        case 'us':
            $sql = "update com_option_config set option_value = '$status' where option_name = 'us_lock' ";
            break;
        default:
            break;
    }
    $db ->query($sql);
    return $db->affectedRows();

}

/**
 * @func  查询ca绑定的方式
 * @return array
 */
function sel_ca_com_option_config()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM com_option_config WHERE option_name = 'ca_channel' and sub_id = 'CA' and status = 1";
    $db->query($sql);
    $rows = $db->fetchAll();
    return $rows;
}

/**
 * @return array
 */
function sel_ba_com_option_config()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM com_option_config WHERE option_name = 'bit_type' and sub_id = 'BA' and status = 1";
    $db->query($sql);
    $rows = $db->fetchAll();
    return $rows;
}


/**
 * @param $type
 * @return array
 */
function getRegPermission($type)
{
    $db = new DB_COM();
    switch ($type) {
        case 'ba':
            $sql = "select option_value as isOpen from com_option_config where option_name = 'ba_lock'";
            break;
        case 'ca':
            $sql = "select option_value as isOpen from com_option_config where option_name = 'ca_lock'";

            break;
        case 'us':
            $sql =  "select option_value as isOpen from com_option_config where option_name = 'user_lock'";
            break;
        default:
            break;
    }
    $db->query($sql);
    return $db->fetchRow();
}

/**
 * @param $type
 * @param $status
 * @return int
 */
function setRegPermission($type, $status)
{
    $db = new DB_COM();
    switch ($type) {
        case 'ba':
            $sql = "update com_option_config set option_value = '$status' where option_name = 'ba_lock'";
            break;
        case 'ca':
            $sql = "update com_option_config set option_value = '$status' where option_name = 'ca_lock'";
            break;
        case 'ba':
            $sql = "update com_option_config set option_value = '$status' where option_name = 'user_lock'";
            break;
        default:
            break;
    }
    $db->query($sql);
    return $db->affectedRows();
}

/**
 * @return array
 */
function getRegPermissionList()
{
    $db = new DB_COM();
    $sql = "select option_name, option_value as is_open from com_option_config where option_name in ('ba_lock', 'ca_lock', 'user_lock')";
    $db->query($sql);
    return $db->fetchAll();
}