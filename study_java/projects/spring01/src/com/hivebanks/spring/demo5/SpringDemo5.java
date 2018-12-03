package com.hivebanks.spring.demo5;

import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @Classname SpringDemo5
 * @Description TODO
 * @Date 2018/11/22 2:59 PM
 * @Created by pool
 */
public class SpringDemo5 {
    @Test
    public void demo1()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        CollectionBean bean = (CollectionBean) context.getBean("collectionBean");
        System.out.println(bean);
    }
}
