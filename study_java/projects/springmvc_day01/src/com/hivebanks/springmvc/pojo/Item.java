package com.hivebanks.springmvc.pojo;

import java.util.Date;

/**
 * @Classname item
 * @Description TODO
 * @Date 2018/12/20 5:13 PM
 * @Created by pool
 */
public class Item {
    private int id;
    // 商品名称
    private String name;
    // 商品价格
    private double price;
    // 商品创建时间
    private Date createtime;
    // 商品描述
    private String detail;

    public Item() {
    }

    public Item(int id, String name, double price, Date createtime, String detail) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.createtime = createtime;
        this.detail = detail;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public Date getCreatetime() {
        return createtime;
    }

    public void setCreatetime(Date createtime) {
        this.createtime = createtime;
    }

    public String getDetail() {
        return detail;
    }

    public void setDetail(String detail) {
        this.detail = detail;
    }
}
