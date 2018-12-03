package com.hivebanks.tx.demo2;

/**
 * @Classname AccountDao
 * @Description TODO
 * @Date 2018/11/26 2:09 PM
 * @Created by pool
 */
public interface AccountDao {
    public void outMoney(String from, double money);
    public void inMoney(String in, double money);
}
