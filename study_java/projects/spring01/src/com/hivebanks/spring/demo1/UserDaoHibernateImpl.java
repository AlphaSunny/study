package com.hivebanks.spring.demo1;

/**
 * @Classname UserDaoHibernateImpl
 * @Description TODO
 * @Date 2018/11/22 11:42 AM
 * @Created by pool
 */
public class UserDaoHibernateImpl implements UserDao {
    @Override
    public void save() {
        System.out.println("UserDaoHibernate 执行了");
    }
}
