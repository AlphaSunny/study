package com.hivebanks.crm.dao.Impl;

import com.hivebanks.crm.dao.LinkmanDao;
import com.hivebanks.crm.domain.Linkman;
import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

/**
 * @Classname LinkmanDaoImpl
 * @Description TODO
 * @Date 2018/12/7 10:44 AM
 * @Created by pool
 */
public class LinkmanDaoImpl extends HibernateDaoSupport implements LinkmanDao {
    @Override
    public void save(Linkman linkman) {
        this.getHibernateTemplate().save(linkman);
    }
}
