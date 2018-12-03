package com.hivebanks.domain;

import javax.servlet.ServletRequest;

/**
 * @Classname Account
 * @Description TODO
 * @Date 2018/11/26 1:29 PM
 * @Created by pool
 */
public class Account {
    private int id;
    private String name;
    private Double balance;

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

    public Double getBalance() {
        return balance;
    }

    public void setBalance(Double balance) {
        this.balance = balance;
    }

    @Override
    public String toString() {
        return "Account{" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                ", balance=" + balance +
                '}';
    }
}
