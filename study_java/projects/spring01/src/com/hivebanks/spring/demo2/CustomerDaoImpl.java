package com.hivebanks.spring.demo2;

/**
 * @Classname CustomerDaoImpl
 * @Description TODO
 * @Date 2018/11/22 11:48 AM
 * @Created by pool
 */
public class CustomerDaoImpl implements CustomerDao {
    @Override
    public void save() {

    }

    public void setup()
    {
        System.out.println("is init");
    }

    public void destroy()
    {
        System.out.println("is destroyed");
    }

}
