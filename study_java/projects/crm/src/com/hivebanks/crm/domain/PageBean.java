package com.hivebanks.crm.domain;

import java.util.List;

/**
 * @Classname PageBean
 * @Description TODO
 * @Date 2018/12/4 3:57 PM
 * @Created by pool
 */
public class PageBean<T> {
    private Integer currPage;
    private Integer pageSize;
    private Integer totalCount;
    private Integer totalPage;
    private List<T> list;

    public Integer getCurrPage() {
        return currPage;
    }

    public void setCurrPage(Integer currPage) {
        this.currPage = currPage;
    }

    public Integer getPageSize() {
        return pageSize;
    }

    public void setPageSize(Integer pageSize) {
        this.pageSize = pageSize;
    }

    public Integer getTotalCount() {
        return totalCount;
    }

    public void setTotalCount(Integer totalCount) {
        this.totalCount = totalCount;
    }

    public Integer getTotalPage() {
        return totalPage;
    }

    public void setTotalPage(Integer totalPage) {
        this.totalPage = totalPage;
    }

    public List<T> getList() {
        return list;
    }

    public void setList(List<T> list) {
        this.list = list;
    }
}
