package com.hivebanks.struts.demo3;

import com.hivebanks.struts.domain.Product;
import com.opensymphony.xwork2.ActionSupport;

import java.util.Map;

public class ProductAction2 extends ActionSupport {
    private Map<String, Product> map;

    public Map<String, Product> getMap() {
        return map;
    }

    public void setMap(Map<String, Product> map) {
        this.map = map;
    }

    @Override
    public String execute() throws Exception {
        for (String key : map.keySet()) {
            Product product = map.get(key);
            System.out.println(key+"    "+product);
        }

        return NONE;
    }
}
