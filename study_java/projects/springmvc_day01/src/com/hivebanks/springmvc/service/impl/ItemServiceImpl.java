package com.hivebanks.springmvc.service.impl;

import com.hivebanks.springmvc.mapper.ItemMapper;
import com.hivebanks.springmvc.pojo.Item;
import com.hivebanks.springmvc.service.ItemService;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.List;

/**
 * @Classname ItemServiceImpl
 * @Description TODO
 * @Date 2018/12/26 2:55 PM
 * @Created by pool
 */
public class ItemServiceImpl implements ItemService {

    @Autowired
    private ItemMapper itemMapper;

    @Override
    public List<Item> getItemList() {
        return null;
    }
}
