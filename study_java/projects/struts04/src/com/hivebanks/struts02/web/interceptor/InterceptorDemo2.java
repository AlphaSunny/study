package com.hivebanks.struts02.web.interceptor;

import com.opensymphony.xwork2.ActionInvocation;
import com.opensymphony.xwork2.interceptor.AbstractInterceptor;

/**
 * @Classname InterceptorDemo2
 * @Description TODO
 * @Date 2018/11/21 3:14 PM
 * @Created by pool
 */
public class InterceptorDemo2 extends AbstractInterceptor {
    @Override
    public String intercept(ActionInvocation actionInvocation) throws Exception {
        System.out.println("Interceptor1 is on");
        String obj = actionInvocation.invoke();
        System.out.println("Interceptor2 is off");
        return null;
    }
}
