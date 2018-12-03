package com.hivebanks.dao.impl;

import com.hivebanks.dao.CustomerDao;
import com.hivebanks.domain.Customer;
import com.hivebanks.utils.HibernateUtils;
import org.hibernate.Session;
import org.hibernate.Transaction;

import java.util.List;

public class CustomerDaoImpl implements CustomerDao {
    @Override
    public List<Customer> find() {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        List<Customer> list = session.createQuery("from Customer").list();
        tx.commit();
        return list;
    }
}
