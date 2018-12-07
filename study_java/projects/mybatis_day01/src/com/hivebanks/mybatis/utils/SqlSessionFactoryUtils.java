package com.hivebanks.mybatis.utils;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

/**
 * @Classname SqlSessionFactoryUtils
 * @Description TODO
 * @Date 2018/12/7 2:23 PM
 * @Created by pool
 */
public class SqlSessionFactoryUtils {

    private static SqlSessionFactory sqlSessionFactory;

    static
    {
        try{

            SqlSessionFactoryBuilder ssfb = new SqlSessionFactoryBuilder();
            InputStream inputStream = Resources.getResourceAsStream("SqlMapConfig.xml");
            sqlSessionFactory = ssfb.build(inputStream);


        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public static SqlSessionFactory getSqlSessionFactory() {
        return sqlSessionFactory;
    }
}
