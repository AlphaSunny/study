package com.hivebanks.struts2.demo2;

import com.opensymphony.xwork2.Action;

public class ActionDemo2 implements Action {
    @Override
    public String execute() throws Exception {
        System.out.println("ActionDemo2执行了...");
        return NONE;
    }
}
