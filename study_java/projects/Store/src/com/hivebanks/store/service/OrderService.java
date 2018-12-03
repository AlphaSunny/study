package com.hivebanks.store.service;

import com.hivebanks.store.domain.Order;
import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.User;

public interface OrderService {
    PageModel findOrdersByUidWithPage(User user, int curNum) throws Exception;

    void saveOrder(Order order) throws Exception;

    Order findOrderByOid(String oid) throws Exception;

    void updateOrder(Order order) throws Exception;
}
