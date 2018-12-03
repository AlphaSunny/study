<?php

function getLaInfo()
{
    $db = new DB_COM();
    $sql = "SELECT * FROM la_admin limit 1";
    $db->query($sql);
    return $db->fetchRow();
}

