package com.hivebanks.crm.service.Impl;

import com.hivebanks.crm.dao.UserDao;
import com.hivebanks.crm.domain.User;
import com.hivebanks.crm.service.UserService;
import com.hivebanks.crm.utils.MD5Utils;
import org.springframework.transaction.annotation.Transactional;

/**
 * @Classname UserServiceImpl
 * @Description TODO
 * @Date 2018/11/29 4:08 PM
 * @Created by pool
 */

@Transactional
public class UserServiceImpl implements UserService {
    private UserDao userDao;

    public void setUserDao(UserDao userDao) {
        this.userDao = userDao;
    }

    @Override
    public void regist(User user) {
        user.setUser_password(MD5Utils.md5(user.getUser_password()));
        user.setUser_state("1");
        // 调用DAO
        userDao.save(user);

    }

    @Override
    public User login(User user) {
        user.setUser_password(MD5Utils.md5(user.getUser_password()));
        return userDao.login(user);

    }
}
