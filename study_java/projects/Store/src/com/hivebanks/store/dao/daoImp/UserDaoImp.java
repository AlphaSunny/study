package com.hivebanks.store.dao.daoImp;

import com.hivebanks.store.dao.UserDao;
import com.hivebanks.store.domain.User;
import com.hivebanks.store.utils.JDBCUtils;
import jdk.nashorn.internal.scripts.JD;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;

import java.sql.SQLException;

public class UserDaoImp implements UserDao {
    @Override
    public User findUserByUserName(String um) throws SQLException {
        String sql = "select * from user where username = ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        return qr.query(sql, new BeanHandler<User>(User.class), um);
    }

    @Override
    public void userRegist(User user01) throws SQLException {
        String sql = "insert into user values (?,?,?,?,?,?,?,?,?,?)";
        Object[] params = {user01.getUid(), user01.getUsername(), user01.getPassword(), user01.getName(), user01.getEmail(), user01.getTelephone(),
                                user01.getBirthday(), user01.getSex(), user01.getState(), user01.getCode()};
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        qr.update(sql, params);

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
        String sql = "select * from user where username = ? and password = ? and state = 1";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        return  qr.query(sql, new BeanHandler<User>(User.class), user01.getUsername(), user01.getPassword());
    }
}
