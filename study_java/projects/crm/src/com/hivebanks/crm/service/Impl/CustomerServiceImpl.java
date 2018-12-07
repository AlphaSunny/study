package com.hivebanks.crm.service.Impl;

import com.hivebanks.crm.dao.CustomerDao;
import com.hivebanks.crm.dao.UserDao;
import com.hivebanks.crm.domain.Customer;
import com.hivebanks.crm.domain.PageBean;
import com.hivebanks.crm.service.CustomerService;
import org.hibernate.criterion.DetachedCriteria;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

/**
 * @Classname CustomerServiceImpl
 * @Description TODO
 * @Date 2018/11/30 1:32 PM
 * @Created by pool
 */
@Transactional
public class CustomerServiceImpl implements CustomerService {
    private CustomerDao customerDao;

    public void setCustomerDao(CustomerDao customerDao) {
        this.customerDao = customerDao;
    }

    @Override
    public void save(Customer customer) {
        customerDao.save(customer);
    }

    @Override
    public PageBean<Customer> findByPage(DetachedCriteria detachedCriteria, Integer currPage, Integer pageSize) {
        PageBean<Customer> pageBean = new PageBean<Customer>();
        // 封装当前页数:
        pageBean.setCurrPage(currPage);
        // 封装每页显示记录数:
        pageBean.setPageSize(pageSize);
        // 封装总记录数:
        // 调用DAO:
        Integer totalCount  = customerDao.findCount(detachedCriteria);
        pageBean.setTotalCount(totalCount);
        // 封装总页数:
        Double tc = totalCount.doubleValue();
        Double num = Math.ceil(tc/pageSize);
        pageBean.setTotalPage(num.intValue());
        // 封装每页显示数据的集合
        Integer begin = (currPage - 1) * pageSize;
        List<Customer> list = customerDao.findByPage(detachedCriteria,begin,pageSize);
        pageBean.setList(list);
        return pageBean;
    }

    @Override
    public List<Customer> findAll() {
        return  customerDao.findAll();
    }


}
