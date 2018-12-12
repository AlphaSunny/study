package com.hivebanks.mybatis.pojo;

import java.util.List;

/**
 * @Classname QueryVo
 * @Description TODO
 * @Date 2018/12/11 5:50 PM
 * @Created by pool
 */
public class QueryVo {
    private User user;

    private List<Integer> ids;

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public List<Integer> getIds() {
        return ids;
    }

    public void setIds(List<Integer> ids) {
        this.ids = ids;
    }
}
