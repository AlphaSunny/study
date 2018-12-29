package com.hivebanks.springmvc.service;

import com.hivebanks.springmvc.pojo.Item;

import java.util.List;

/**
 * @Classname ItemService
 * @Description TODO
 * @Date 2018/12/26 2:54 PM
 * @Created by pool
 */
public interface ItemService {
    /**
     * 获取商品列表
     * @return
     */
    List<Item> getItemList();

    Item getItemById(Integer id);

    void updateItem(Item item);
}
