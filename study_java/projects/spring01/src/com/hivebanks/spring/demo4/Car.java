package com.hivebanks.spring.demo4;

/**
 * @Classname Car
 * @Description TODO
 * @Date 2018/11/22 2:08 PM
 * @Created by pool
 */
public class Car {
    private String name;
    private Double price;

    public Car(String name, Double price) {
        super();
        this.name = name;
        this.price = price;
    }

    @Override
    public String toString() {
        return "car{" +
                "name='" + name + '\'' +
                ", price=" + price +
                '}';
    }
}

