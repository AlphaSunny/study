package com.hivebanks.mybatis.test;


import com.hivebanks.mybatis.dao.UserDao;
import com.hivebanks.mybatis.pojo.User;
import org.junit.Before;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.web.context.support.XmlWebApplicationContext;

/**
 * @Classname UserDaoTest
 * @Description TODO
 * @Date 2018/12/14 11:28 AM
 * @Created by pool
 */
public class UserDaoTest {
    private ApplicationContext applicationContext;

    @Before
    public void init()
    {
        applicationContext = new ClassPathXmlApplicationContext("classpath:applicationContext.xml");
    }

    @Test
    public void testGetUserById()
    {
        UserDao dao = applicationContext.getBean(UserDao.class);
        User user = dao.getUserById(30);
        System.out.println(user);
    }


}
