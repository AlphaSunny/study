package com.hivebanks.mybatis.mapper;

import com.hivebanks.mybatis.pojo.User;

/**
 * @Classname UserMapper
 * @Description TODO
 * @Date 2018/12/14 11:17 AM
 * @Created by pool
 */
public interface UserMapper {
    User getUserById(Integer id);
}
