package com.hivebanks.store.domain;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class Order {
    private String oid;  //订单ID
    private Date orderTime;//下单时间
    private int   state;//状态 1:下单未付款 2付款未发货 3发货未收货 4收货结束

    private double total;//总计

    private String address;  //收货人地址
    private String name;  //收货人姓名
    private String telephone;  //收货人电话

    //private String uid;
    //1_user可以携带更多数据
    //2_面向对象角度:对象关联对象
    private User user;
    private List<OrderItem> list=new ArrayList<OrderItem>();


    public Order(String oid, Date orderTime, int state, double total, String address, String name, String telephone, User user, List<OrderItem> list) {
        this.oid = oid;
        this.orderTime = orderTime;
        this.state = state;
        this.total = total;
        this.address = address;
        this.name = name;
        this.telephone = telephone;
        this.user = user;
        this.list = list;
    }

    public List<OrderItem> getList() {
        return list;
    }

    public void setList(List<OrderItem> list) {
        this.list = list;
    }


    public Order() {
    }

    public String getOid() {
        return oid;
    }

    public void setOid(String oid) {
        this.oid = oid;
    }

    public Date getOrderTime() {
        return orderTime;
    }

    public void setOrderTime(Date orderTime) {
        this.orderTime = orderTime;
    }

    public int getState() {
        return state;
    }

    public void setState(int state) {
        this.state = state;
    }

    public double getTotal() {
        return total;
    }

    public void setTotal(double total) {
        this.total = total;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getTelephone() {
        return telephone;
    }

    public void setTelephone(String telephone) {
        this.telephone = telephone;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }


}
