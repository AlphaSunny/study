package com.hivebanks.dao;

import com.hivebanks.domain.Customer;

import java.util.List;

public interface CustomerDao {
    public List<Customer> find();
}
