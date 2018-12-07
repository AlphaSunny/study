package com.hivebanks.crm.dao.impl;

import com.hivebanks.crm.dao.CustomerDao;
import com.hivebanks.crm.domain.Customer;
import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import java.util.List;

/**
 * @Classname CustomerDaoImpl
 * @Description TODO
 * @Date 2018/12/6 3:38 PM
 * @Created by pool
 */
public class CustomerDaoImpl extends HibernateDaoSupport implements CustomerDao {
    public List<Customer> findAll() {
        return null;
    }
}
