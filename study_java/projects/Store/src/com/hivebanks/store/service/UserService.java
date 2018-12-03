package com.hivebanks.store.service;

import com.hivebanks.store.domain.User;

import java.sql.SQLException;

public interface UserService {
    User findUserByUserName(String um)throws SQLException;

    void userRegist(User user01)throws SQLException;

    User userActive(String code)throws SQLException;

    void updateUser(User user01)throws SQLException;

    User userLogin(User user01)throws SQLException;
}
