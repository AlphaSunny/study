package com.hivebanks.springmvc.controller;

import com.hivebanks.springmvc.pojo.Item;
import com.hivebanks.springmvc.service.ItemService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.Arrays;
import java.util.Date;
import java.util.List;

/**
 * @Classname ItemController
 * @Description TODO
 * @Date 2018/12/20 5:12 PM
 * @Created by pool
 */

@Controller
public class ItemController {

    @Autowired
    private ItemService itemService;

    @RequestMapping("itemList")
    public ModelAndView itemList()
    {
        ModelAndView mav = new ModelAndView();

        List<Item> itemList = itemService.getItemList();

        mav.addObject("itemList", itemList);
        // mav.setViewName("/WEB-INF/jsp/itemList.jsp");
        mav.setViewName("itemList");
        return mav;
    }

}
