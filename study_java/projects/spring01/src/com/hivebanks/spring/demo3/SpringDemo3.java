package com.hivebanks.spring.demo3;

import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @Classname SpringDemo3
 * @Description TODO
 * @Date 2018/11/22 1:29 PM
 * @Created by pool
 */
public class SpringDemo3 {
    @Test
    public void demo1()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        Bean1 bean1 = (Bean1) context.getBean("bean1");
    }

    @Test
    public void demo2()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        Bean2 bean2 = (Bean2) context.getBean("bean2");
        System.out.println(bean2);

    }

    @Test
    /**
     * 实例工厂实例化
     */
    public void demo3(){
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("applicationContext.xml");
        Bean3 bean3 = (Bean3) applicationContext.getBean("bean3");
        System.out.println(bean3);
    }


}
