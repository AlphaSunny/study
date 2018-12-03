package com.hivebanks.spring.demo2;

import org.junit.Test;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @Classname SpringDemo2
 * @Description TODO
 * @Date 2018/11/22 11:53 AM
 * @Created by pool
 */
public class SpringDemo2 {

    @Test
    public void demo1()
    {
        ClassPathXmlApplicationContext applicationContext = new ClassPathXmlApplicationContext("applicationContext.xml");
        CustomerDao customerDao = (CustomerDao) applicationContext.getBean("customerDao");
        customerDao.save();
        applicationContext.close();
    }


    @Test
    /**
     * Bean的作用范围配置
     */
    public void demo2(){
        ClassPathXmlApplicationContext applicationContext= new ClassPathXmlApplicationContext("applicationContext.xml");
        CustomerDao customerDAO1 = (CustomerDao) applicationContext.getBean("customerDao");
        System.out.println(customerDAO1);
        CustomerDao customerDAO2 = (CustomerDao) applicationContext.getBean("customerDao");
        System.out.println(customerDAO2);
        System.out.println(customerDAO1==customerDAO2);
        applicationContext.close();
    }


}
