package com.hivebanks.mybatis.dao.impl;

import com.hivebanks.mybatis.dao.UserDao;
import com.hivebanks.mybatis.pojo.User;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import java.util.List;

/**
 * @Classname UserDaoImpl
 * @Description TODO
 * @Date 2018/12/14 11:14 AM
 * @Created by pool
 */
public class UserDaoImpl extends SqlSessionDaoSupport implements UserDao {
    @Override
    public User getUserById(Integer id) {
        return null;
    }

    @Override
    public List<User> getUserByUserName(String userName) {
        return null;
    }

    @Override
    public void insertUser(User user) {

    }
}
