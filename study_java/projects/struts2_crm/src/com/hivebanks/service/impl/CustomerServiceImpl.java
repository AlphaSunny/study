package com.hivebanks.service.impl;

import com.hivebanks.dao.CustomerDao;
import com.hivebanks.dao.impl.CustomerDaoImpl;
import com.hivebanks.domain.Customer;
import com.hivebanks.service.CustomerService;

import java.util.List;

public class CustomerServiceImpl implements CustomerService {

    @Override
    public List<Customer> find() {
        CustomerDao customerDao = new CustomerDaoImpl();
        return customerDao.find();
    }
}
