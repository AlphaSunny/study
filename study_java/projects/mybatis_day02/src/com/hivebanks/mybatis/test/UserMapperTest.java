package com.hivebanks.mybatis.test;

import com.hivebanks.mybatis.mapper.UserMapper;
import com.hivebanks.mybatis.pojo.QueryVo;
import com.hivebanks.mybatis.pojo.User;
import com.hivebanks.mybatis.utils.SqlSessionFactoryUtils;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.junit.Test;

import java.util.Date;
import java.util.List;

/**
 * @Classname UserMapperTest
 * @Description TODO
 * @Date 2018/12/11 5:58 PM
 * @Created by pool
 */
public class UserMapperTest {
    @Test
    public void test_getUserById()
    {
        SqlSession sqlSession = SqlSessionFactoryUtils.getSqlSessionFactory().openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
        User user = userMapper.getUserById(26);
        System.out.println(user);
        sqlSession.close();
    }

    @Test
    public void testGetUserByUserName() {
        SqlSession sqlSession = SqlSessionFactoryUtils.getSqlSessionFactory().openSession();
        //获取接口的代理人实现类
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        List<User> list = userMapper.getUserByUserName("张");
        for (User user : list) {
            System.out.println(user);
        }
        sqlSession.close();
    }


    @Test
    public void testInsertUser()
    {
        SqlSession sqlSession = SqlSessionFactoryUtils.getSqlSessionFactory().openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        User user = new User();
        user.setUsername("徐文");
        user.setSex("1");
        user.setBirthday(new Date());
        user.setAddress("安徽");
        userMapper.insertUser(user);

        sqlSession.commit();
        sqlSession.close();
    }

    @Test
    public void testGetUserByQueryVo() {
        SqlSession sqlSession = SqlSessionFactoryUtils.getSqlSessionFactory().openSession();
        //获取接口的代理人实现类
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
        QueryVo vo = new QueryVo();
        User user2 = new User();
        user2.setUsername("张");

        vo.setUser(user2);

        List<User> list = userMapper.getUserByQueryVo(vo);
        for (User user : list) {
            System.out.println(user);
        }
        sqlSession.close();
    }
}
