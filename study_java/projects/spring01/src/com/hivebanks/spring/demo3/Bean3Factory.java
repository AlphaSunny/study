package com.hivebanks.spring.demo3;

/**
 * @Classname Bean3Factory
 * @Description TODO
 * @Date 2018/11/22 1:27 PM
 * @Created by pool
 */
public class Bean3Factory {
    public Bean3 createBean3()
    {
        System.out.println("bean3实例工厂执行了");
        return new Bean3();
    }
}
