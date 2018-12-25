package com.hivebanks.mybatis.test;

import com.hivebanks.mybatis.dao.UserDao;
import com.hivebanks.mybatis.pojo.User;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @Classname UserDaoTest
 * @Description TODO
 * @Date 2018/12/25 2:15 PM
 * @Created by pool
 */
public class UserDaoTest {

    @Test
    public void test1()
    {
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("classpath:applicationContext.xml");
        UserDao dao = applicationContext.getBean(UserDao.class);
        User user = dao.getUserById(26);
        System.out.println(user);
    }
}
