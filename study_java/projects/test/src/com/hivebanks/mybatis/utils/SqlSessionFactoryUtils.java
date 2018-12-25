package com.hivebanks.mybatis.utils;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

/**
 * @Classname SqlSessionFactoryUtils
 * @Description TODO
 * @Date 2018/12/25 1:46 PM
 * @Created by pool
 */
public class SqlSessionFactoryUtils {
    private static SqlSessionFactory sqlSessionFactory;

    static {
        try {
            // 创建SqlSessionFactoryBuilder对象
            SqlSessionFactoryBuilder ssfb = new SqlSessionFactoryBuilder();
            // 创建核心配置文件的输入流
            InputStream inputStream = Resources.getResourceAsStream("SqlMapConfig.xml");
            // 通过输入流创建SqlSessionFactory对象
            sqlSessionFactory = ssfb.build(inputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * 获取SqlSessionFactory
     * @return
     */
    public static SqlSessionFactory getSqlSessionFactory() {
        return sqlSessionFactory;
    }
}
