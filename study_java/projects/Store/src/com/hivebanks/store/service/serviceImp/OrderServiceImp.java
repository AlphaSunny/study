package com.hivebanks.store.service.serviceImp;

import com.hivebanks.store.dao.OrderDao;
import com.hivebanks.store.dao.daoImp.OrderDaoImp;
import com.hivebanks.store.domain.Order;
import com.hivebanks.store.domain.OrderItem;
import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.User;
import com.hivebanks.store.service.OrderService;
import com.hivebanks.store.utils.JDBCUtils;

import java.util.List;

public class OrderServiceImp implements OrderService {

    OrderDao orderDao = new OrderDaoImp();
    @Override
    public PageModel findOrdersByUidWithPage(User user, int curNum) throws Exception {
        int totalRecords = orderDao.findTotalRecordsByUid(user);
        PageModel pm = new PageModel(curNum, totalRecords, 3);

        List<Order> list = orderDao.findOrdersByUidWithPage(user.getUid(), pm.getStartIndex(), pm.getPageSize());
        pm.setList(list);
        pm.setUrl("OrderServlet?method=findOrdersByUidWithPage");
        return pm;
    }

    @Override
    public void saveOrder(Order order) throws Exception{
        try {
            JDBCUtils.startTransaction();
            orderDao.saveOrder(order);
            for(OrderItem item:order.getList()){
                orderDao.saveOrderItem(item);
            }
            JDBCUtils.commitAndClose();
        } catch (Exception e) {
            JDBCUtils.rollbackAndClose();
            e.printStackTrace();
        }
    }

    @Override
    public Order findOrderByOid(String oid) throws Exception{
        return orderDao.findOrderByOid(oid);
    }

    @Override
    public void updateOrder(Order order) throws Exception {
        orderDao.updateOrder(order);
    }


}
