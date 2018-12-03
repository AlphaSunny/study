package com.hivebanks.ssh.service.Impl;

import com.hivebanks.ssh.dao.CustomerDao;
import com.hivebanks.ssh.service.CustomerService;
import org.springframework.transaction.annotation.Transactional;

/**
 * @Classname CustomerServiceImpl
 * @Description TODO
 * @Date 2018/11/27 1:59 PM
 * @Created by pool
 */

@Transactional
public class CustomerServiceImpl implements CustomerService {
    private CustomerDao customerDao;

    public void setCustomerDao(CustomerDao customerDao) {
        this.customerDao = customerDao;
    }
    @Override
    public void save(CustomerService customer) {

    }
}
