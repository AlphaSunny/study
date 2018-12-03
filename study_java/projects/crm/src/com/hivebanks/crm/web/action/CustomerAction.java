package com.hivebanks.crm.web.action;

import com.hivebanks.crm.domain.Customer;
import com.hivebanks.crm.service.CustomerService;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

/**
 * @Classname CustomerAction
 * @Description TODO
 * @Date 2018/11/30 1:29 PM
 * @Created by pool
 */
public class CustomerAction extends ActionSupport implements ModelDriven<Customer> {
    private Customer customer = new Customer();
    @Override
    public Customer getModel() {
        return null;
    }

    private CustomerService customerService;

    public void setCustomerService(CustomerService customerService) {
        this.customerService = customerService;
    }

    public String saveUI()
    {
        return "saveUI";
    }

    public String findAll()
    {
        System.out.println("findall");
        return "win";
    }

}
