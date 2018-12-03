package com.hivebanks.struts.demo1;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;

import java.util.Arrays;
import java.util.Map;

public class RequestDemo1 extends ActionSupport {
    @Override
    public String execute() throws Exception {
        //接收数据
        ActionContext context = ActionContext.getContext();
        Map<String, Object> map = context.getParameters();
        for (String key : map.keySet()) {
            String[] values = (String[]) map.get(key);
            System.out.println(key+"    "+ Arrays.toString(values));
        }

        context.put("reqName", "reqValue");
        context.getSession().put("sessName", "seseValue");
        context.getApplication().put("appName", "appValue");
        return SUCCESS;
    }
}
