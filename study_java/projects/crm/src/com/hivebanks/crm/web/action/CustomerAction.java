package com.hivebanks.crm.web.action;

import com.hivebanks.crm.domain.Customer;
import com.hivebanks.crm.domain.PageBean;
import com.hivebanks.crm.service.CustomerService;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;
import org.hibernate.criterion.DetachedCriteria;

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
        return customer;
    }

    private CustomerService customerService;

    public void setCustomerService(CustomerService customerService) {
        this.customerService = customerService;
    }

    //设置当前叶
    private Integer currPage = 1;
    public void setCurrPage(Integer currPage) {
        this.currPage = currPage;
    }

    //设置
    private Integer pageSize = 1;

    public void setPageSize(Integer pageSize) {
        this.pageSize = pageSize;
    }

    public String saveUI()
    {
        return "saveUI";
    }

    public String findAll()
    {
        DetachedCriteria detachedCriteria = DetachedCriteria.forClass(Customer.class);

        PageBean<Customer> pageBean = customerService.findByPage(detachedCriteria, currPage, pageSize);
        System.out.println(pageBean.getList().size());
        ActionContext.getContext().getValueStack().push(pageBean);
        return "findAll";
    }

    public String save()
    {
        customerService.save(customer);
        return NONE;
    }


}
