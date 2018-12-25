package com.hivebanks.mybatis.dao.impl;

import com.hivebanks.mybatis.dao.UserDao;
import com.hivebanks.mybatis.pojo.User;
import org.apache.ibatis.session.SqlSession;
import org.mybatis.spring.support.SqlSessionDaoSupport;

import java.util.List;

/**
 * @Classname UserDaoImpl
 * @Description TODO
 * @Date 2018/12/25 2:06 PM
 * @Created by pool
 */
public class UserDaoImpl extends SqlSessionDaoSupport implements UserDao {
    @Override
    public User getUserById(Integer id) {
        SqlSession sqlSession= super.getSqlSession();
        User user = sqlSession.selectOne("user.getUserById", id);
        //这里不能关闭SqlSession
        //sqlSession.close();
        return user;
    }

    @Override
    public List<User> getUserByName(String name) {
        SqlSession session = super.getSqlSession();
        List<User> users= session.selectList("user.getUserByUsername", name);

        return users;
    }
}
