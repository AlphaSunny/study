package com.hivebanks.spring.demo1;

/**
 * @Classname UserDaoImpl
 * @Description TODO
 * @Date 2018/11/22 11:40 AM
 * @Created by pool
 */
public class UserDaoImpl implements UserDao {
    private String name;

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public void save() {
        System.out.println("UserDaoImpl is on  " + name);
    }
}
