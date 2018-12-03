package com.hivebanks.hibernate.demo1;

import com.hivebanks.hibernate.domain.Customer;
import com.hivebanks.hibernate.domain.LinkMan;
import com.hivebanks.hibernate.utils.HibernateUtils;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

public class HibernateDemo1 {
    @Test
    public void demo1(){
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        // 创建一个客户
        Customer customer = new Customer();
        customer.setCust_name("李向文");

        for (int i = 1; i <= 10; i++) {
            LinkMan linkMan = new LinkMan();
            linkMan.setLkm_name("王东" + i);
            linkMan.setCustomer(customer);

            customer.getLinkMans().add(linkMan);

            session.save(linkMan);
        }
        session.save(customer);

        tx.commit();
    }

    @Test
    public void demo2(){
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        Query query = session.createQuery("from Customer");
        List<Customer> list = query.list();

        for (Customer c: list)
        {
            System.out.println(c);
        }

        tx.commit();
    }


    @Test
    public  void demo3()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        Query query = session.createQuery("select c from Customer c");
        List<Customer> list = query.list();

        for (Customer c: list)
            System.out.println(c);

        tx.commit();
    }

    @Test
    public void demo5()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        Query query = session.createQuery("from Customer where cust_source = :aaa and cust_name like :bbb");
        query.setParameter("aaa", "朋友推荐");
        query.setParameter("bbb", "李%");
        List<Customer> list = query.list();
        for (Customer c : list)
            System.out.println(c);
        tx.commit();
    }

    @Test
    public void demo6()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        Query query = session.createQuery("select new Customer(cust_name, cust_source) from Customer");
        List<Customer> list = query.list();
        for (Customer c: list)
            System.out.println(c);
        tx.commit();
    }

    @Test
    public void demo7()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        Query query = session.createQuery("from LinkMan");
        List<LinkMan> list = query.list();
        for (LinkMan l: list)
            System.out.println(l);
        tx.commit();
    }

    @Test
    public void demo8()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        Object object = session.createQuery("select count(*) from Customer").uniqueResult();
        System.out.println(object);
        List<Object[]> list = session.createQuery("select cust_source , count(*) from Customer group by cust_source").list();
        for (Object[] objects : list) {
            System.out.println(Arrays.toString(objects));
        }
        tx.commit();
    }

    @Test
    public void demo9()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        List<Customer> list = session.createQuery("select distinct c from Customer c inner join fetch c.linkMans").list();

        for (Customer c: list)
        {
            System.out.println(c);
        }
        tx.commit();
    }
}
