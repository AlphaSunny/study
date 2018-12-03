package com.hivebanks.store.service.serviceImp;

import com.hivebanks.store.dao.UserDao;
import com.hivebanks.store.domain.User;
import com.hivebanks.store.service.UserService;
import com.hivebanks.store.utils.BeanFactory;

import java.sql.SQLException;

public class UserServiceImp implements UserService {
    UserDao userDao = (UserDao) BeanFactory.createObject("UserDao");

    @Override
    public User findUserByUserName(String um) throws SQLException {
        User user = userDao.findUserByUserName(um);
        return user;
    }

    @Override
    public void userRegist(User user01) throws SQLException {
        userDao.userRegist(user01);
    }

    @Override
    public User userActive(String code) throws SQLException {
        return null;
    }

    @Override
    public void updateUser(User user01) throws SQLException {

    }

    @Override
    public User userLogin(User user01) throws SQLException {
        User user = userDao.userLogin(user01);
        return user;
    }
}
