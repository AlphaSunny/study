package com.hivebanks.spring.demo1;

import javafx.application.Application;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @Classname SpringDemo1
 * @Description TODO
 * @Date 2018/11/22 11:53 AM
 * @Created by pool
 */
public class SpringDemo1 {
    @Test
    public void demo1()
    {
        UserDaoImpl userDao = new UserDaoImpl();
        userDao.setName("yang");
        userDao.save();
    }

    @Test
    public void demo2()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        UserDao userDao = (UserDao) context.getBean("userDao");
        userDao.save();

    }
}
