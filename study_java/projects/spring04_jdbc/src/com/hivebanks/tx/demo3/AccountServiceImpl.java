package com.hivebanks.tx.demo3;

import org.springframework.transaction.annotation.Isolation;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

/**
 * @Classname AccountServiceImpl
 * @Description TODO
 * @Date 2018/11/26 2:11 PM
 * @Created by pool
 */

@Transactional(isolation= Isolation.DEFAULT,propagation= Propagation.REQUIRED)
public class AccountServiceImpl implements AccountService {
    private AccountDao accountDao;

    public void setAccountDao(AccountDao accountDao) {
        this.accountDao = accountDao;
    }



    @Override
    public void transfer(String from, String to, Double money) {
        accountDao.outMoney(from, money);
        accountDao.inMoney(to, money);
    }
}
