package com.hivebanks.spring.demo1;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import javax.annotation.Resource;

/**
 * @Classname SpringDemo1
 * @Description TODO
 * @Date 2018/11/27 1:26 PM
 * @Created by pool
 */

@RunWith(SpringJUnit4ClassRunner.class )
@ContextConfiguration("classpath:applicationContext.xml")
public class SpringDemo1 {
    @Resource(name = "orderDao")
    private OrderDao orderDao;

    @Test
    public void demo1()
    {
        orderDao.save();
        orderDao.delete();
        orderDao.update();
        orderDao.find();
    }

}
