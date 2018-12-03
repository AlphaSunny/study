<?php

session_start();

/**
 * @func: get current user
 * @return: String
 */
function xiu_get_current_user()
{
    if(empty($_SESSION['current_login_user'])) {
        header("Location", "/admin/login.php");
        exit();
    }
    return $_SESSION['current_login_user'];
}