package com.hivebanks.store.domain;

import java.util.List;

public class PageModel {
    private int currentPageNum;
    private int pageSize = 5;
    private int totalRecords;

    private int totalPageNum;
    private int startIndex;
    private int prePageNum;
    private int nextPageNum;


    //页码按钮
    private int startPage;
    private int endPage;


    private List list;
    private String url;

    //要想使用我的分页，必须给我两个参数。一个是要看哪一页，另一个是总记录条数
    public PageModel(int currentPageNum,int totalRecords,int pageSize){
        this.currentPageNum = currentPageNum;
        this.totalRecords = totalRecords;
        this.pageSize=pageSize;

        //计算查询记录的开始索引
        startIndex = (currentPageNum-1)*pageSize;
        //计算总页数
        totalPageNum = totalRecords%pageSize==0?(totalRecords/pageSize):(totalRecords/pageSize+1);


        startPage = currentPageNum - 4; //5
        endPage = currentPageNum + 4;  //13
        //看看总页数够不够9页
        if(totalPageNum>9){
            //超过了9页
            if(startPage < 1){
                startPage = 1;
                endPage = startPage+8;
            }
            if(endPage>totalPageNum){
                endPage = totalPageNum;
                startPage = endPage-8;
            }
        }else{
            //不够9页
            startPage = 1;
            endPage = totalPageNum;
        }
    }

    public int getCurrentPageNum() {
        return currentPageNum;
    }

    public void setCurrentPageNum(int currentPageNum) {
        this.currentPageNum = currentPageNum;
    }

    public int getPageSize() {
        return pageSize;
    }

    public void setPageSize(int pageSize) {
        this.pageSize = pageSize;
    }

    public int getTotalRecords() {
        return totalRecords;
    }

    public void setTotalRecords(int totalRecords) {
        this.totalRecords = totalRecords;
    }

    public int getTotalPageNum() {
        return totalPageNum;
    }

    public void setTotalPageNum(int totalPageNum) {
        this.totalPageNum = totalPageNum;
    }

    public int getStartIndex() {
        return startIndex;
    }

    public void setStartIndex(int startIndex) {
        this.startIndex = startIndex;
    }

    public int getPrePageNum() {
        return prePageNum;
    }

    public void setPrePageNum(int prePageNum) {
        this.prePageNum = prePageNum;
    }

    public int getNextPageNum() {
        return nextPageNum;
    }

    public void setNextPageNum(int nextPageNum) {
        this.nextPageNum = nextPageNum;
    }

    public int getStartPage() {
        return startPage;
    }

    public void setStartPage(int startPage) {
        this.startPage = startPage;
    }

    public int getEndPage() {
        return endPage;
    }

    public void setEndPage(int endPage) {
        this.endPage = endPage;
    }

    public List getList() {
        return list;
    }

    public void setList(List list) {
        this.list = list;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }
}
