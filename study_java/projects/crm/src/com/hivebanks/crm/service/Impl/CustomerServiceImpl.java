package com.hivebanks.crm.service.Impl;

import com.hivebanks.crm.dao.CustomerDao;
import com.hivebanks.crm.dao.UserDao;
import com.hivebanks.crm.service.CustomerService;

/**
 * @Classname CustomerServiceImpl
 * @Description TODO
 * @Date 2018/11/30 1:32 PM
 * @Created by pool
 */
public class CustomerServiceImpl implements CustomerService {
    private CustomerDao customerDao;

    public void setCustomerDao(CustomerDao customerDao) {
        this.customerDao = customerDao;
    }
}
