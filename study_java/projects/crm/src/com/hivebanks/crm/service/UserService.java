package com.hivebanks.crm.service;

import com.hivebanks.crm.domain.User;

/**
 * @Classname UserService
 * @Description TODO
 * @Date 2018/11/29 4:07 PM
 * @Created by pool
 */
public interface UserService {
    void regist(User user);

    User login(User user);
}
