package com.hivebanks.struts.demo2;

import com.hivebanks.struts.domain.User;
import com.opensymphony.xwork2.ActionSupport;

public class UserAction2 extends ActionSupport {
    private User user;
    public User getUser()
    {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    @Override
    public String execute() throws Exception {
        System.out.println(user);
        return NONE;
    }
}
