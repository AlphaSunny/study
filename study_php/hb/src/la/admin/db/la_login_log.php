<?php


/**
 * @func 登陆失败计数：登陆错误超过三次则限制登陆30分钟
 * @param $user
 * @param $login_time
 * @return int
 *
 */
function getLaLoginFail($user, $login_time) {
    $db = new DB_COM();
    $login_time -= 1800;
    $sql = "SELECT log_id FROM la_login_log WHERE login_status = 0 AND user = '$user' AND login_time > '$login_time'";
    $db->query($sql);
    return $db->affectedRows();
}

/**
 * @param $fail
 */
function recordLaLoginFail($fail)
{
    $db = new DB_COM();
    $sql = $db->sqlInsert('la_login_log', $fail);
    $db->query($sql);
}

/**
 * @param $data
 * @return int
 */
function logLogin($data)
{
    $db = new DB_COM();
    $sql = $db->sqlInsert('la_login_log', $data);
    $res = $db->query($sql);
    if($res == 0)
        return 0;
    return $db->insertID();
}