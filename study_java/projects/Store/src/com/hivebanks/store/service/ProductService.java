package com.hivebanks.store.service;

import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.Product;

import java.sql.SQLException;
import java.util.List;

public interface ProductService {

    List<Product> findNewProducts()throws SQLException;

    List<Product> findHotProducts()throws SQLException ;

    Product findProductByPid(String pid)throws SQLException ;

    PageModel findProductsWithCidAndPage(String cid, int curNum)throws SQLException ;

    void saveProduct(Product product)throws SQLException ;
}
