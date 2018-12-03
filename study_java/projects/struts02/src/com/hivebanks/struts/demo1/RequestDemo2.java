package com.hivebanks.struts.demo1;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.ServletActionContext;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Map;

public class RequestDemo2 extends ActionSupport {
    @Override
    public String execute() throws Exception {
        HttpServletRequest request = ServletActionContext.getRequest();
        Map<String, String[]> map = request.getParameterMap();
        for(String key: map.keySet())
        {
            String[] values = map.get(key);
            System.out.println(key + "   " + Arrays.toString(values));
        }
        request.setAttribute("reqValue", "reqValue");
        request.getSession().setAttribute("sessName", "sessValue");
        ServletActionContext.getServletContext().setAttribute("appName", "appValue");
        return SUCCESS;
    }
}
