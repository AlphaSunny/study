package com.hivebanks.springmvc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

/**
 * @Classname HelloControl
 * @Description TODO
 * @Date 2018/12/28 1:40 PM
 * @Created by pool
 */
@Controller
public class HelloControl {
    @RequestMapping("hello")
    public ModelAndView hello(){
        System.out.println("hello springmvc...");
        ModelAndView mav = new ModelAndView();
        //设置模型数据，用于传递到jsp
        mav.addObject("msg", "hello springmvc......");
        //设置视图名字，用于响应用户
        mav.setViewName("/WEB-INF/jsp/hello.jsp");

        return mav;
    }
}
