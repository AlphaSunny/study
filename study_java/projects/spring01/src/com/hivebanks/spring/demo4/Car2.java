package com.hivebanks.spring.demo4;

/**
 * @Classname Car2
 * @Description TODO
 * @Date 2018/11/22 1:58 PM
 * @Created by pool
 */
public class Car2 {
    private String name;
    private double price;

    public void setName(String name) {
        this.name = name;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return "Car2{" +
                "name='" + name + '\'' +
                ", price=" + price +
                '}';
    }
}
