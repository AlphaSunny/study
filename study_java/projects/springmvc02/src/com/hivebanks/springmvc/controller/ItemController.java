package com.hivebanks.springmvc.controller;

import com.hivebanks.springmvc.pojo.Item;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.Arrays;
import java.util.Date;
import java.util.List;

/**
 * @Classname ItemController
 * @Description TODO
 * @Date 2018/12/28 3:00 PM
 * @Created by pool
 */

@Controller
public class ItemController {
    @RequestMapping("itemList")
    public ModelAndView itemList() {
        ModelAndView mav = new ModelAndView();
        //模拟查询商品列表
        List<Item> list = Arrays.asList(new Item(1, "冰箱", 1999, new Date(), "冰箱很冷"), new Item(2, "冰箱2", 1999, new Date(), "冰箱很冷2"),
                new Item(3, "冰箱3", 1999, new Date(), "冰箱很冷3"),new Item(4, "冰箱4", 1999, new Date(), "冰箱很热"));
        mav.addObject("itemList", list);
        //mav.setViewName("/WEB-INF/jsp/itemList.jsp");
        mav.setViewName("itemList");
        return mav;
    }
}
