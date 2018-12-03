package com.hivebanks.spring.demo5;

import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * @Classname CollectionBean
 * @Description TODO
 * @Date 2018/11/22 2:57 PM
 * @Created by pool
 */
public class CollectionBean {
    private String[] arrs;
    private List<String> list;
    private Set<String> set;
    private Map<String, String> map;

    public void setArrs(String[] arrs) {
        this.arrs = arrs;
    }

    public void setList(List<String> list) {
        this.list = list;
    }

    public void setSet(Set<String> set) {
        this.set = set;
    }

    public void setMap(Map<String, String> map) {
        this.map = map;
    }

    @Override
    public String toString() {
        return "CollectionBean{" +
                "arrs=" + Arrays.toString(arrs) +
                ", list=" + list +
                ", set=" + set +
                ", map=" + map +
                '}';
    }
}
