package com.hivebanks.mybatis.dao;

import com.hivebanks.mybatis.pojo.User;

import java.util.List;

/**
 * @Classname UserDao
 * @Description TODO
 * @Date 2018/12/25 1:49 PM
 * @Created by pool
 */
public interface UserDao {
    User getUserById(Integer id);
    List<User> getUserByName(String name);
}
