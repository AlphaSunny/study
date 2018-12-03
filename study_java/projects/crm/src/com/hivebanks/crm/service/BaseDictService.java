package com.hivebanks.crm.service;

import com.hivebanks.crm.domain.BaseDict;

import java.util.List;

/**
 * @Classname BaseDictService
 * @Description TODO
 * @Date 2018/12/3 2:00 PM
 * @Created by pool
 */
public interface BaseDictService {
    List<BaseDict> findByTypeCode(String dict_type_code);
}
