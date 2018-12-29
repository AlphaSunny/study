package com.hivebanks.springmvc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

/**
 * @Classname HelloControll
 * @Description TODO
 * @Date 2018/12/28 2:53 PM
 * @Created by pool
 */
@Controller
public class HelloControll {
    @RequestMapping("hello")
    public ModelAndView hello()
    {
        System.out.println("hello springmvc...");
        ModelAndView mav = new ModelAndView();
        //设置模型数据，用于传递到jsp
        mav.addObject("msg", "hello springmvc......");
        //设置视图名字，用于响应用户
        mav.setViewName("hello");
        return mav;
    }
}

