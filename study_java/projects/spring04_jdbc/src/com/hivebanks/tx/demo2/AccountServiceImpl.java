package com.hivebanks.tx.demo2;

import com.hivebanks.tx.demo2.AccountDao;
import org.springframework.transaction.support.TransactionTemplate;

/**
 * @Classname AccountServiceImpl
 * @Description TODO
 * @Date 2018/11/26 2:11 PM
 * @Created by pool
 */
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
