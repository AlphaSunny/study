package com.hivebanks.jdbc.demo1;

import com.mchange.v2.c3p0.DriverManagerDataSource;
import org.junit.Test;
import org.springframework.jdbc.core.JdbcTemplate;

/**
 * @Classname JdbcDemo1
 * @Description TODO
 * @Date 2018/11/26 11:42 AM
 * @Created by pool
 */
public class JdbcDemo1 {
    @Test
    public void demo1()
    {
        DriverManagerDataSource dataSource = new DriverManagerDataSource();
        dataSource.setDriverClass("com.mysql.jdbc.Driver");
        dataSource.setJdbcUrl("jdbc:mysql:///spring04");
        dataSource.setUser("root");
        dataSource.setPassword("123456");

        JdbcTemplate template = new JdbcTemplate();
        template.setDataSource(dataSource);
        template.update("insert into account values (null,?,?)", "赵冠希",10000d);
    }


}
