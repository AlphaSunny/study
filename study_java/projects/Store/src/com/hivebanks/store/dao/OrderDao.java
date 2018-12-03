package com.hivebanks.store.dao;

import com.hivebanks.store.domain.Order;
import com.hivebanks.store.domain.OrderItem;
import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.User;

import java.sql.SQLException;
import java.util.List;

public interface OrderDao {
    List<Order> findOrdersByUidWithPage(String uid, int startIndex, int pageSize ) throws SQLException;

    int findTotalRecordsByUid(User user) throws SQLException;

    void saveOrder(Order order) throws SQLException;

    void saveOrderItem(OrderItem item) throws SQLException;

    Order findOrderByOid(String oid) throws  SQLException;

    void updateOrder(Order order) throws SQLException;
}
