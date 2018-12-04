package com.hivebanks.crm.dao;

import com.hivebanks.crm.domain.Customer;
import org.hibernate.criterion.DetachedCriteria;

import java.util.List;

/**
 * @Classname CustomerDao
 * @Description TODO
 * @Date 2018/11/30 1:33 PM
 * @Created by pool
 */
public interface CustomerDao {
    void save(Customer customer);

    Integer findCount(DetachedCriteria detachedCriteria);

    List<Customer> findByPage(DetachedCriteria detachedCriteria, Integer begin, Integer pageSize);
}
