package com.hivebanks.struts2.demo3;

import com.opensymphony.xwork2.ActionSupport;

public class UserAction extends ActionSupport {
    public String find()
    {
        System.out.println("find user");
        return NONE;
    }

    public String update()
    {
        System.out.println("update user");
        return NONE;
    }

    public String delete()
    {
        System.out.println("delete user");
        return NONE;
    }

    public  String save()
    {
        System.out.println("save");
        return NONE;
    }
}
