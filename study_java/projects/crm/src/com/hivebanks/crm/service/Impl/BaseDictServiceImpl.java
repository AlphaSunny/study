package com.hivebanks.crm.service.Impl;

import com.hivebanks.crm.dao.BaseDictDao;
import com.hivebanks.crm.domain.BaseDict;
import com.hivebanks.crm.service.BaseDictService;

import java.util.List;

/**
 * @Classname BaseDictServiceImpl
 * @Description TODO
 * @Date 2018/12/3 2:01 PM
 * @Created by pool
 */
public class BaseDictServiceImpl implements BaseDictService {
    private BaseDictDao baseDictDao;

    public void setBaseDictDao(BaseDictDao baseDictDao) {
        this.baseDictDao = baseDictDao;
    }

    @Override
    public List<BaseDict> findByTypeCode(String dict_type_code) {
        return baseDictDao.findByTypeCode(dict_type_code);
    }
}
