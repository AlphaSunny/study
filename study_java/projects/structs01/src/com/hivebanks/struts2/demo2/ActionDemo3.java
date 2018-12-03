package com.hivebanks.struts2.demo2;

import com.opensymphony.xwork2.ActionSupport;

public class ActionDemo3 extends ActionSupport {
    @Override
    public String execute() throws Exception
    {
        System.out.println("demo3执行了");
        return NONE;
    }
}
