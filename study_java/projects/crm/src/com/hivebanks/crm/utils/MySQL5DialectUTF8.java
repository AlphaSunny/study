package com.hivebanks.crm.utils;

import org.hibernate.dialect.MySQL5InnoDBDialect;
import org.hibernate.dialect.MySQLDialect;
import org.hibernate.dialect.MySQLInnoDBDialect;

/**
 * @Classname MySQL5DialectUTF8
 * @Description TODO
 * @Date 2018/12/4 3:27 PM
 * @Created by pool
 */
public class MySQL5DialectUTF8 extends MySQL5InnoDBDialect {
    @Override
    public String getTableTypeString() {
        return " ENGINE=InnoDB DEFAULT CHARSET=utf8";
    }

}
