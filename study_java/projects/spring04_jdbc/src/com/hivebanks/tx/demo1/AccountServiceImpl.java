package com.hivebanks.tx.demo1;

import com.hivebanks.domain.Account;
import org.springframework.transaction.support.TransactionTemplate;

/**
 * @Classname AccountServiceImpl
 * @Description TODO
 * @Date 2018/11/26 2:11 PM
 * @Created by pool
 */
public class AccountServiceImpl implements AccountService {
    private AccountDao accountDao;
    private TransactionTemplate transactionTemplate;

    public void setAccountDao(AccountDao accountDao) {
        this.accountDao = accountDao;
    }

    public void setTransactionTemplate(TransactionTemplate transactionTemplate) {
        this.transactionTemplate = transactionTemplate;
    }


    @Override
    public void transfer(String from, String to, Double money) {
        accountDao.outMoney(from, money);
        accountDao.inMoney(to, money);
    }
}
