package com.hivebanks.hibernate.demo1;

import com.hivebanks.hibernate.domain.Customer;
import com.hivebanks.hibernate.domain.LinkMan;
import com.hivebanks.hibernate.utils.HibernateUtils;
import org.hibernate.Session;
import org.hibernate.Transaction;
import org.junit.Test;

public class HibernateDemo1 {
    @Test
    // 保存2个客户  和 3个联系人  并且建立好关系
    public void demo1(){
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        // 创建两个客户
        Customer customer1 = new Customer();
        customer1.setCust_name("王东");
        Customer customer2 = new Customer();
        customer2.setCust_name("赵洪");

        // 创建三个联系人
        LinkMan linkMan1 = new LinkMan();
        linkMan1.setLkm_name("凤姐");
        LinkMan linkMan2 = new LinkMan();
        linkMan2.setLkm_name("如花");
        LinkMan linkMan3 = new LinkMan();
        linkMan3.setLkm_name("旺财");

        // 设置关系:
        linkMan1.setCustomer(customer1);
        linkMan2.setCustomer(customer1);
        linkMan3.setCustomer(customer2);
        customer1.getLinkMans().add(linkMan1);
        customer1.getLinkMans().add(linkMan2);
        customer2.getLinkMans().add(linkMan3);

        // 保存数据:
        session.save(linkMan1);
        session.save(linkMan2);
        session.save(linkMan3);
        session.save(customer1);
        session.save(customer2);

        tx.commit();
    }


    @Test
    public void demo2()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();
        Customer customer = new Customer();
        customer.setCust_name("曹哥");

        LinkMan linkMan = new LinkMan();
        linkMan.setLkm_name("曹二");
        customer.getLinkMans().add(linkMan);
        linkMan.setCustomer(customer);

        session.save(customer);
        session.save(linkMan);

        tx.commit();
    }

    @Test
    public void demo3()
    {
        Session session = HibernateUtils.getCurrentSession();
        Transaction tx = session.beginTransaction();

        Customer customer = new Customer();
        customer.setCust_name("赵洪");

        LinkMan linkMan = new LinkMan();
        linkMan.setLkm_name("如花");

        customer.getLinkMans().add(linkMan);
        linkMan.setCustomer(customer);

        session.save(customer);


        tx.commit();
    }

}
