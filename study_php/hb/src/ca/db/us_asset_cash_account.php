<?php


function get_us_asset_cash_account_info_by_account_id($account_id)
{
    $db = new DB_COM();
    $sql = "SELECT * FROM us_asset_cash_account where account_id = '{$account_id}' limit 1";
    $db -> query($sql);
    $row = $db ->fetchRow();
    return $row;
}
