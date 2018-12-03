package com.hivebanks.struts.demo2;

import com.hivebanks.struts.domain.User;
import com.opensymphony.xwork2.ActionSupport;
import com.sun.tools.internal.xjc.reader.xmlschema.bindinfo.BIConversion;

import java.util.Date;

public class UserAction1 extends ActionSupport {
    // 提供了对应的属性
    private String username;
    private String password;
    private Integer age;
    private Date birthday;
    private Double salary;

    public void setUsername(String username) {
        this.username = username;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public void setBirthday(Date birthday) {
        this.birthday = birthday;
    }

    public void setSalary(Double salary) {
        this.salary = salary;
    }

    @Override
    public String execute() throws Exception {
        System.out.println(username);
        System.out.println(password);
        System.out.println(age);
        System.out.println(birthday);
        System.out.println(salary);

        User user = new User();
        user.setUsername(username);
        user.setPassword(password);
        user.setAge(age);
        user.setBirthday(birthday);
        user.setSalary(salary);
        return NONE;
    }
}
