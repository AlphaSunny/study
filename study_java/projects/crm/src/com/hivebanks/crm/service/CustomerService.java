package com.hivebanks.crm.service;

import com.hivebanks.crm.domain.Customer;
import com.hivebanks.crm.domain.PageBean;
import org.hibernate.criterion.DetachedCriteria;

import java.util.List;

/**
 * @Classname CustomerService
 * @Description TODO
 * @Date 2018/11/30 1:30 PM
 * @Created by pool
 */
public interface CustomerService {

    void save(Customer customer);

    PageBean<Customer> findByPage(DetachedCriteria detachedCriteria, Integer currPage, Integer pageSize);

    List<Customer> findAll();
}
