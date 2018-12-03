package com.hivebanks.struts02.web.interceptor;

import com.opensymphony.xwork2.ActionInvocation;
import com.opensymphony.xwork2.interceptor.AbstractInterceptor;

/**
 * @Classname InterceptorDemo1
 * @Description TODO
 * @Date 2018/11/21 3:13 PM
 * @Created by pool
 */
public class InterceptorDemo1 extends AbstractInterceptor {
    @Override
    public String intercept(ActionInvocation actionInvocation) throws Exception {
        System.out.println("InterceptorDemo1执行了...");
        String obj = actionInvocation.invoke();
        System.out.println("InterceptorDemo1执行结束了...");
        return obj;
    }
}
