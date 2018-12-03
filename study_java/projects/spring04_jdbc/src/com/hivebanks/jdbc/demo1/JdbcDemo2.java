package com.hivebanks.jdbc.demo1;

import com.hivebanks.domain.Account;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import javax.annotation.Resource;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

/**
 * @Classname JdbcDemo2
 * @Description TODO
 * @Date 2018/11/26 11:57 AM
 * @Created by pool
 */

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("classpath:applicationContext.xml")
public class JdbcDemo2 {
    @Resource( name ="jdbcTemplate")
    private JdbcTemplate jdbcTemplate;


    @Test
    public void demo1()
    {
        jdbcTemplate.update("insert into account values (null, ?, ?)", "何菊花", 10000d);
    }

    @Test
    //modify
    public void demo2()
    {
        jdbcTemplate.update("update account set name = ?, balance = ? where id =?", "yang", 2000d, 1);

    }
    //delete
    @Test
    public void demo3()
    {
        jdbcTemplate.update("delete from account where id = ?", 2);
    }


    @Test
    //find
    public void demo4()
    {
        String name = jdbcTemplate.queryForObject("select name from account where id = ?", String.class, 1);
        System.out.println(name);

    }

    @Test
    public void demo5()
    {
        Long num = jdbcTemplate.queryForObject("select count(*) from account", Long.class);
        System.out.println(num);
    }

    @Test
    public void demo6()
    {
        Account account = jdbcTemplate.queryForObject("select * from Account where id = ?", new MyRowMapper(), 1);
        System.out.println(account);
    }

    @Test
    public void demo7()
    {
        List<Account> list = jdbcTemplate.query("select * from account", new MyRowMapper());
        for(Account account: list)
        {
            System.out.println(account);
        }
    }


    class MyRowMapper implements RowMapper<Account> {

        @Override
        public Account mapRow(ResultSet rs, int rowNum) throws SQLException {
            Account account = new Account();
            account.setId(rs.getInt("id"));
            account.setName(rs.getString("name"));
            account.setBalance(rs.getDouble("balance"));
            return account;
        }

    }
}
