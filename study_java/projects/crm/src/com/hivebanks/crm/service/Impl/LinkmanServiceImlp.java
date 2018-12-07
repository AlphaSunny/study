package com.hivebanks.crm.service.Impl;


import com.hivebanks.crm.dao.LinkmanDao;
import com.hivebanks.crm.domain.Linkman;
import com.hivebanks.crm.service.LinkmanService;

/**
 * @Classname LinkmanServiceImlp
 * @Description TODO
 * @Date 2018/12/7 10:43 AM
 * @Created by pool
 */
public class LinkmanServiceImlp implements LinkmanService {
    private LinkmanDao linkmanDao;


    public void setLinkmanDao(LinkmanDao linkmanDao) {
        this.linkmanDao = linkmanDao;
    }

    @Override
    public void save(Linkman linkman) {
        linkmanDao.save(linkman);
    }
}
