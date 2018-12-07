package com.hivebanks.crm.dao.impl;

import com.hivebanks.crm.dao.CustomerDao;
import com.hivebanks.crm.domain.Customer;

import java.util.List;

/**
 * @Classname CustomerDaoImpl
 * @Description TODO
 * @Date 2018/12/6 1:59 PM
 * @Created by pool
 */
public class CustomerDaoImpl extends HibernateDaoSupport implements CustomerDao  {
    @Override
    public List<Customer> findAll() {
        return null;
    }
}
