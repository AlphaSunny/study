package com.hivebanks.store.dao.daoImp;

import com.hivebanks.store.dao.OrderDao;
import com.hivebanks.store.domain.Order;
import com.hivebanks.store.domain.OrderItem;
import com.hivebanks.store.domain.Product;
import com.hivebanks.store.domain.User;
import com.hivebanks.store.utils.JDBCUtils;
import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.MapListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;


import java.sql.SQLException;
import java.util.List;
import java.util.Map;

public class OrderDaoImp implements OrderDao {
    @Override
    public List<Order> findOrdersByUidWithPage(String uid, int startIndex, int pageSize) throws SQLException {
        String sql = "select * from orders where uid = ? order by ordertime desc limit ?, ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());

        List<Order> list= qr.query(sql, new BeanListHandler<Order>(Order.class), uid, startIndex, pageSize);
        for(Order order:list){
            sql="SELECT * FROM  orderitem o , product p WHERE o.pid=p.pid  AND oid=?";
            List<Map<String, Object>> list01 = qr.query(sql, new MapListHandler(),order.getOid());
            popOrder(order, list01);
        }

        return list;
    }

    @Override
    public int findTotalRecordsByUid(User user) throws SQLException{
        String sql = "select count(*) from orders where uid = ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        Long num = (Long)qr.query(sql, new ScalarHandler(), user.getUid());
        return num.intValue();
    }

    @Override
    public void saveOrder(Order order) throws  SQLException {
        String sql = "insert into orders values (?,?,?,?,?,?,?,?)";
        Object[] params = {order.getOid(), order.getOrderTime(), order.getTotal(), order.getState(), order.getAddress(), order.getName(), order.getTelephone(), order.getUser().getUid()};
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        qr.update(sql, params);

    }

    @Override
    public void saveOrderItem(OrderItem item) throws SQLException {
        String sql = "insert into orderitem values (?,?,?,?,?)";
        Object[] params = {item.getItemid(), item.getQuantity(), item.getTotal(), item.getProduct().getPid(), item.getOrder().getOid()};
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        qr.update(sql, params);
    }

    @Override
    public Order findOrderByOid(String oid) throws SQLException{
        String sql = "select * from orders where oid = ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        Order order = qr.query(sql, new BeanHandler<Order>(Order.class), oid);
        sql = "select * from orderitem o, product p where o.pid = p.pid and oid = ? ";
        List<Map<String, Object>> list = qr.query(sql, new MapListHandler(), oid);
        popOrder(order, list);
        return order;
    }

    @Override
    public void updateOrder(Order order) throws SQLException {
        String sql = "update orders set ordertime = ?, total= ?, state=?, address=?, name = ?, telephone = ? where oid =?";
        Object[] params = {order.getOrderTime(), order.getTotal(), order.getState(), order.getAddress(),order.getName(), order.getTelephone(), order.getOid()};
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        qr.update(sql, params);
    }


    public void popOrder(Order order, List<Map<String, Object>> list )
    {
        for(Map<String, Object> map: list)
        {
            Product Product =new Product();
            OrderItem OrderItem=new OrderItem();
            try {
                BeanUtils.populate(Product, map);
                BeanUtils.populate(OrderItem, map);
            } catch (Exception e) {
                e.printStackTrace();
            }

            OrderItem.setProduct(Product);
            order.getList().add(OrderItem);
        }
    }
}
