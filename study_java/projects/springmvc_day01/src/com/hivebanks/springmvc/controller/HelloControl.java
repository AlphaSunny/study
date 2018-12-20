package com.hivebanks.springmvc.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

/**
 * @Classname HelloControl
 * @Description TODO
 * @Date 2018/12/20 4:39 PM
 * @Created by pool
 */
@Controller
public class HelloControl {
    @RequestMapping("hello")
    public ModelAndView hello()
    {
        System.out.println("hello");
        ModelAndView mav = new ModelAndView();
        mav.addObject("msg", "hello spring mvc");
        mav.setViewName("/WEB-INF/jsp/hello.jsp");
        return mav;
    }
}
