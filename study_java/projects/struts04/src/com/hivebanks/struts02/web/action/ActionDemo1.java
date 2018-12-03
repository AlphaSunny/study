package com.hivebanks.struts02.web.action;

import com.opensymphony.xwork2.ActionSupport;

/**
 * @Classname ActionDemo1
 * @Description TODO
 * @Date 2018/11/21 3:11 PM
 * @Created by pool
 */
public class ActionDemo1 extends ActionSupport {
    @Override
    public String execute() throws Exception {
        System.out.println("ActionDemo1 成功了");
        return super.execute();
    }
}
