package com.hivebanks.store.dao;

import com.hivebanks.store.domain.User;

import java.sql.SQLException;

public interface UserDao {
    User findUserByUserName(String um)throws SQLException;

    void userRegist(User user01)throws SQLException;

    User userActive(String code)throws SQLException;

    void updateUser(User user01)throws SQLException;

    User userLogin(User user01)throws SQLException;
}
