package com.hivebanks.mybatis.test;

import com.hivebanks.mybatis.pojo.User;
import com.hivebanks.mybatis.utils.SqlSessionFactoryUtils;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Test;

import java.io.InputStream;
import java.util.List;

/**
 * @Classname MybatisTest
 * @Description TODO
 * @Date 2018/12/7 2:07 PM
 * @Created by pool
 */
public class MybatisTest {
    @Test
    public void test() throws Exception
    {
        SqlSessionFactoryBuilder ssfb = new SqlSessionFactoryBuilder();
        InputStream inputStream = Resources.getResourceAsStream("SqlMapConfig.xml");

        SqlSessionFactory sessionFactory = ssfb.build(inputStream);

        SqlSession sqlSession= sessionFactory.openSession();

        User user = sqlSession.selectOne("user.getUserById", 1);

        System.out.println(user);

        sqlSession.close();

    }

    @Test
    public void test1()
    {
        SqlSessionFactory sessionFactory = SqlSessionFactoryUtils.getSqlSessionFactory();

        SqlSession sqlSession = sessionFactory.openSession();

        List<User> list = sqlSession.selectList("user.getUserByUsername", "%张%");
        for (User user: list)
            System.out.println(user);

        sqlSession.close();

    }

}
