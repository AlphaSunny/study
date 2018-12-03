package com.hivebanks.spring.demo4;

import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

/**
 * @Classname SpringDemo4
 * @Description TODO
 * @Date 2018/11/22 2:05 PM
 * @Created by pool
 */
public class SpringDemo4 {
    @Test
    public void demo1()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        Car car= (Car)context.getBean("car");
        System.out.println(car);
    }

    @Test
    public  void  demo2()
    {
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        Car2 car = (Car2) context.getBean("Car2");
        System.out.println(car);
    }

    @Test
    public void demo3(){
        ApplicationContext applicationContext = new ClassPathXmlApplicationContext("applicationContext.xml");
        Employee employee = (Employee) applicationContext.getBean("employee");
        System.out.println(employee);
    }
}
