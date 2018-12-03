package com.hivebanks.crm.dao;

import com.hivebanks.crm.domain.BaseDict;

import java.util.List;

/**
 * @Classname BaseDictDao
 * @Description TODO
 * @Date 2018/12/3 2:07 PM
 * @Created by pool
 */
public interface BaseDictDao {
    List<BaseDict> findByTypeCode(String dict_type_code);
}
