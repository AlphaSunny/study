package com.hivebanks.mybatis.dao;

import com.hivebanks.mybatis.pojo.User;

import java.util.List;

/**
 * @Classname UserDao
 * @Description TODO
 * @Date 2018/12/14 11:13 AM
 * @Created by pool
 */
public interface UserDao {
    User getUserById(Integer id);
    /**
     * 根据用户名查找用户列表
     * @param userName
     * @return
     */
    List<User> getUserByUserName(String userName);

    /**
     * 添加用户
     * @param user
     */
    void insertUser(User user);
}
