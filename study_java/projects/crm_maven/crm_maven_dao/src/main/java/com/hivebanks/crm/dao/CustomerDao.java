package com.hivebanks.crm.dao;

import com.hivebanks.crm.domain.Customer;

import java.util.List;

/**
 * @Classname CustomerDao
 * @Description TODO
 * @Date 2018/12/6 1:58 PM
 * @Created by pool
 */
public interface CustomerDao {
    public List<Customer> findAll();
}