package com.hivebanks.crm.dao.Impl;

import com.hivebanks.crm.dao.BaseDictDao;
import com.hivebanks.crm.domain.BaseDict;
import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import java.util.List;

/**
 * @Classname BaseDictDaoImpl
 * @Description TODO
 * @Date 2018/12/3 2:08 PM
 * @Created by pool
 */
public class BaseDictDaoImpl extends HibernateDaoSupport implements BaseDictDao {

    @Override
    public List<BaseDict> findByTypeCode(String dict_type_code) {
        return (List<BaseDict>) this.getHibernateTemplate().find("from BaseDict where dict_type_code = ? ", dict_type_code);
    }


}
