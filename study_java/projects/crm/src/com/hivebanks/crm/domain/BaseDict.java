package com.hivebanks.crm.domain;

/**
 * @Classname BaseDict
 * @Description TODO
 * @Date 2018/12/3 1:43 PM
 * @Created by pool
 */
public class BaseDict {

    private String dict_id;
    private String dict_type_code;
    private String dict_type_name;
    private String item_name;
    private String item_code;
    private int dict_sort;
    private String dict_enable;
    private String dict_memo;

    public String getDict_id() {
        return dict_id;
    }

    public void setDict_id(String dict_id) {
        this.dict_id = dict_id;
    }

    public String getDict_type_code() {
        return dict_type_code;
    }

    public void setDict_type_code(String dict_type_code) {
        this.dict_type_code = dict_type_code;
    }

    public String getDict_type_name() {
        return dict_type_name;
    }

    public void setDict_type_name(String dict_type_name) {
        this.dict_type_name = dict_type_name;
    }

    public String getItem_name() {
        return item_name;
    }

    public void setItem_name(String item_name) {
        this.item_name = item_name;
    }

    public String getItem_code() {
        return item_code;
    }

    public void setItem_code(String item_code) {
        this.item_code = item_code;
    }

    public int getDict_sort() {
        return dict_sort;
    }

    public void setDict_sort(int dict_sort) {
        this.dict_sort = dict_sort;
    }

    public String getDict_enable() {
        return dict_enable;
    }

    public void setDict_enable(String dict_enable) {
        this.dict_enable = dict_enable;
    }

    public String getDict_memo() {
        return dict_memo;
    }

    public void setDict_memo(String dict_memo) {
        this.dict_memo = dict_memo;
    }
}
