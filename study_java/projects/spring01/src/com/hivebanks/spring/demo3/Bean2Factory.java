package com.hivebanks.spring.demo3;

/**
 * @Classname Bean2Factory
 * @Description TODO
 * @Date 2018/11/22 1:26 PM
 * @Created by pool
 */
public class Bean2Factory {
    public static Bean2 createBean2()
    {
        System.out.println("Bean2Factory方法执行了");
        return new Bean2();
    }
}
