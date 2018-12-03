package com.hivebanks.ssh.dao.Impl;

import com.hivebanks.ssh.dao.CustomerDao;
import com.hivebanks.ssh.domain.Customer;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

/**
 * @Classname CustomerDaoImpl
 * @Description TODO
 * @Date 2018/11/27 2:02 PM
 * @Created by pool
 */
public class CustomerDaoImpl extends HibernateDaoSupport implements CustomerDao {
    @Override
    public void save(Customer customer) {
        System.out.println("save function is on");
        this.getHibernateTemplate().save(customer);
    }
}
