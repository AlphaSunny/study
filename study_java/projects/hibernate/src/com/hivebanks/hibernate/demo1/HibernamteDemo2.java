package com.hivebanks.hibernate.demo1;

import com.hivebanks.hibernate.utils.HibernateUtils;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.Test;

import java.io.Serializable;

public class HibernamteDemo2 {
    @Test
    public void demo1()
    {
        Session session = HibernateUtils.openSession();
        Transaction tx = session.beginTransaction();

        Customer customer = new Customer();
        customer.setCust_name("周");
        Serializable id = session.save(customer);
        System.out.print(id);
        tx.commit();
        session.close();
    }

    @Test
    public void demo2()
    {
        Session session = HibernateUtils.openSession();
        Transaction tx = session.beginTransaction();

        Customer customer = session.load(Customer.class, 2l);
        System.out.println(customer);
        tx.commit();
        session.close();
    }


    @Test
    // 修改操作
    public void demo3(){
        Session session = HibernateUtils.openSession();
        Transaction tx = session.beginTransaction();

        // 直接创建对象，进行修改
		/*Customer customer = new Customer();
		customer.setCust_id(1l);
		customer.setCust_name("王聪");
		session.update(customer);*/

        // 先查询，再修改(推荐)
        Customer customer = session.get(Customer.class, 1l);
        customer.setCust_name("chris wang");
        session.update(customer);

        tx.commit();
        session.close();
    }

    @Test
    public void demo4()
    {
        Session session = HibernateUtils.openSession();
        Transaction tx = session.beginTransaction();
        Customer customer = session.get(Customer.class, 2l);
        session.delete(customer);
        tx.commit();
        session.close();

    }

}
