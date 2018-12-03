package com.hivebanks.struts.demo2;

import com.hivebanks.struts.domain.User;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class UserAction3 extends ActionSupport implements ModelDriven<User> {
    private User user = new User();
    @Override
    public User getModel() {
        return user;
    }

    @Override
    public String execute() throws Exception {
        System.out.println(user);
        return NONE;
    }
}
