package com.hivebanks.tx.demo1;

import org.springframework.jdbc.core.support.JdbcDaoSupport;

/**
 * @Classname AccountDaoImpl
 * @Description TODO
 * @Date 2018/11/26 2:10 PM
 * @Created by pool
 */
public class AccountDaoImpl extends JdbcDaoSupport implements AccountDao {
    @Override
    public void outMoney(String from, double money) {
        this.getJdbcTemplate().update("update account set balance = balance - ? where name = ?", money, from);
    }

    @Override
    public void inMoney(String in, double money) {
        this.getJdbcTemplate().update("update account set balance = balance + ? where name = ?", money, in);

    }
}
