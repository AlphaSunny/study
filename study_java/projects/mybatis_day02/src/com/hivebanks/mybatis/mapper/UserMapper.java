package com.hivebanks.mybatis.mapper;

import com.hivebanks.mybatis.pojo.QueryVo;
import com.hivebanks.mybatis.pojo.User;

import java.util.List;

/**
 * @Classname UserMapper
 * @Description TODO
 * @Date 2018/12/11 5:59 PM
 * @Created by pool
 */
public interface UserMapper {
    User getUserById(Integer id);

    List<User> getUserByUserName(String name);

    void insertUser(User user);

    List<User> getUserByQueryVo(QueryVo vo);

}
