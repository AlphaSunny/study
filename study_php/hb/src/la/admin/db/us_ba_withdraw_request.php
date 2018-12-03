<?php
/**
 * @func：获得ba对应的用户所有提取资金总和
 * @param $begin_limit_time:起始时间
 * @param $end_limit_time:结束时间
 * @return array
 */
function get_ba_sum_us_ba_withdraw_request_info($begin_limit_time,$end_limit_time)
{
    $when ='';
    if($begin_limit_time){
        $when .= "tx_time >= '{$begin_limit_time}'";
    }
    if($end_limit_time) {
        if ($when) {
            $when .= "AND tx_time <= '{$end_limit_time}'";
        } else {
            $when .= "tx_time <= '{$end_limit_time}'";
        }
    }
    if($when){
        $sql = "SELECT sum(base_amount) FROM us_ba_recharge_request where $when";
    }else{
        $sql = "SELECT sum(base_amount) FROM us_ba_recharge_request ";
    }
    $db = new DB_COM();
    $db->query($sql);
    $row = $db->fetchRow();
    return $row;
}

