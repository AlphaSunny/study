package com.hivebanks.crm.web.action;

import com.hivebanks.crm.domain.Customer;
import com.hivebanks.crm.domain.Linkman;
import com.hivebanks.crm.service.CustomerService;
import com.hivebanks.crm.service.LinkmanService;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;
import org.apache.struts2.interceptor.ServletRequestAware;

import java.util.List;

/**
 * @Classname LinkmanAction
 * @Description TODO
 * @Date 2018/12/7 10:14 AM
 * @Created by pool
 */
public class LinkmanAction extends ActionSupport implements ModelDriven<Linkman> {
    private Linkman linkman = new Linkman();
    @Override
    public Linkman getModel() {
        return linkman;
    }

    private LinkmanService linkmanService;

    public void setLinkmanService(LinkmanService linkmanService) {
        this.linkmanService = linkmanService;
    }

    private CustomerService customerService;

    public void setCustomerService(CustomerService customerService) {
        this.customerService = customerService;
    }

    public String saveUI()
    {
        List<Customer> list = customerService.findAll();
        ActionContext.getContext().getValueStack().set("list", list);
        return "saveUI";
    }

    public String save()
    {
        linkmanService.save(linkman);
        return "saveSuccess";
    }
}
