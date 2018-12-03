package com.hivebanks.spring.demo4;

/**
 * @Classname carInfo
 * @Description TODO
 * @Date 2018/11/22 2:00 PM
 * @Created by pool
 */
public class carInfo {
    private String name;

    public String getName() {
        return "摩托车";
    }

    public Double calculatorPrice(){
        return Math.random() * 3000;
    }
}
