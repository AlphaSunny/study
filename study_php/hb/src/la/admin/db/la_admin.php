<?php
/**
 * @param $id
 * @return array
 */
function get_la_by_id($id){
    $db = new DB_COM();
    $sql = "select * from la_admin where id='{$id}' ";
    $db->query($sql);
    $row = $db->fetchRow();
    return $row;
}

/**
 * @func：检查是否登陆成功
 * @param $username
 * @param $passwordHash
 * @return bool
 */
function log_check($username, $passwordHash)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM la_admin WHERE user= '$username' and pwd = '$passwordHash'";
    $db -> query($sql);
    $row = $db->fetchRow();
    if($row)
        return true;
    return false;
}

/**
 * @param $user
 * @param $ip_login
 * @param $city_login
 * @param $time_login
 * @return int
 *
 * 更新用户登陆记录（最近一次登陆时间，城市，ip）
 */
function login_la_update($user,$ip_login,$city_login,$time_login){

    $db = new DB_COM();
    $sql = "update la_admin set last_login_time = '{$time_login}' , last_login_city='{$city_login}' , last_login_ip='{$ip_login}'
            where user = '{$user}'";
    $db -> query($sql);
    $count = $db -> affectedRows();
    return $count;

}

/**
 * @func 登陆成功后，la的信息和可见菜单
 * @param $user
 * @return array
 * 登陆成功返回 用户信息和可见菜单
 */
function getLaPermission($user)
{

    $db = new DB_COM();
    $sql = "select id,user,real_name,pid,last_login_time,last_login_city,last_login_ip from la_admin where user='{$user}'";
    $db->query($sql);
    $res = $db->fetchRow();

    $return_array = array();
    $pid_array = array();
    $pid_array = explode(',',$res['pid']);
    $pid_list  = array();
    foreach ($pid_array as $pid){

        $sql = "select pname,subname from la_permit where pid='{$pid}'";
        $db->query($sql);
        $pid_single = $db->fetchAll();
        $pid_list[] = $pid_single;

    }
    $return_array['menu'] = $pid_list;
    $return_array['user_info'] = $res;

    return $return_array;

}

