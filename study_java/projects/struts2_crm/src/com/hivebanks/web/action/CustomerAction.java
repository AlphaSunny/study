package com.hivebanks.web.action;

import com.hivebanks.domain.Customer;
import com.hivebanks.service.CustomerService;
import com.hivebanks.service.impl.CustomerServiceImpl;
import com.opensymphony.xwork2.ActionSupport;
import org.apache.struts2.ServletActionContext;

import java.util.List;

public class CustomerAction extends ActionSupport {
    public String find()
    {
        CustomerService customerService = new CustomerServiceImpl();
        List<Customer> list = customerService.find();
        ServletActionContext.getRequest().setAttribute("list", list);
        return "findSuccess";
    }
}
