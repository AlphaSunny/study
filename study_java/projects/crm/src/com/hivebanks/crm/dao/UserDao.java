package com.hivebanks.crm.dao;

import com.hivebanks.crm.domain.User;

/**
 * @Classname UserDao
 * @Description TODO
 * @Date 2018/11/29 4:10 PM
 * @Created by pool
 */
public interface UserDao {
    void save(User user);

    User login(User user);
}
