package com.hivebanks.hibernate.demo1;

import com.hivebanks.hibernate.domain.Customer;
import com.hivebanks.hibernate.domain.LinkMan;
import com.hivebanks.hibernate.utils.HibernateUtils;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Restrictions;
import org.junit.Test;

import java.util.List;

public class HibernateDemo2 {
    @Test
    public void demo1()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        Criteria criteria = session.createCriteria(Customer.class);
        List<Customer> list = criteria.list();
        for (Customer c: list)
            System.out.println(c);
        tx.commit();
    }

    @Test
    /**
     * 排序查询
     */
    public void demo2(){
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        // 排序查询
        Criteria criteria = session.createCriteria(Customer.class);
//		criteria.addOrder(Order.asc("cust_id")); // 升序
        criteria.addOrder(Order.desc("cust_id")); // 降序
        List<Customer> list = criteria.list();

        for (Customer customer : list) {
            System.out.println(customer);
        }

        tx.commit();
    }

    @Test
    /**
     * 分页查询
     */
    public void demo3(){
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        // 分页查询
        Criteria criteria = session.createCriteria(LinkMan.class);
        criteria.setFirstResult(10);
        criteria.setMaxResults(10);
        List<LinkMan> list = criteria.list();

        for (LinkMan linkMan : list) {
            System.out.println("1");
            System.out.println(linkMan);
        }
        tx.commit();

    }

    @Test
    /**
     * 条件查询
     */
    public void demo4(){
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        // 条件查询
        Criteria criteria = session.createCriteria(Customer.class);
        // 设置条件:
        /**
         * =   eq
         * >   gt
         * >=  ge
         * <   lt
         * <=  le
         * <>  ne
         * like
         * in
         * and
         * or
         */
        criteria.add(Restrictions.eq("cust_source", "小广告"));
//		criteria.add(Restrictions.or(Restrictions.like("cust_name", "李%")));
        criteria.add(Restrictions.like("cust_name", "李%"));
        List<Customer> list = criteria.list();
        for (Customer customer : list) {
            System.out.println(customer);
        }
        tx.commit();
    }



}
