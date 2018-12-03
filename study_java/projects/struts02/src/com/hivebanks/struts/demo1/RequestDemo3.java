package com.hivebanks.struts.demo1;

import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.interceptor.ServletRequestAware;
import org.apache.struts2.util.ServletContextAware;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import java.util.Arrays;
import java.util.Map;


public class RequestDemo3 extends ActionSupport implements ServletRequestAware, ServletContextAware {

    private HttpServletRequest request;
    private ServletContext context;

    public RequestDemo3() {
        super();
        System.out.println("RequestDemo3被创建了...");
    }

    @Override
    public String execute() throws Exception {
        Map<String, String[]> map = request.getParameterMap();
        for (String key : map.keySet()) {
            String[] values = map.get(key);
            System.out.println(key+"    "+ Arrays.toString(values));
        }
        // 二、向域对象中保存数据
        // 向request域中保存数据
        request.setAttribute("reqName", "reqValue");
        // 向session中保存数据:
        request.getSession().setAttribute("sessName", "sessValue");
        // 向application中保存数据:
        context.setAttribute("appName", "appValue");
        return super.execute();
    }

    @Override
    public void setServletRequest(HttpServletRequest httpServletRequest) {
        this.request = httpServletRequest;
    }

    @Override
    public void setServletContext(ServletContext servletContext) {
        this.context = servletContext;

    }
}
