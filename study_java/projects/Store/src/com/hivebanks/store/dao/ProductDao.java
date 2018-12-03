package com.hivebanks.store.dao;

import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.Product;

import java.sql.SQLException;
import java.util.List;

public interface ProductDao {
    List<Product> findNewProducts()throws SQLException;

    List<Product> findHotProducts()throws SQLException ;

    Product findProductByPid(String pid)throws SQLException ;

    List<Product> findProductsWithCidAndPage(String cid, int startIndex, int pageSize)throws SQLException ;

    void saveProduct(Product product)throws SQLException ;

    int findTotalNum(String cid)throws SQLException;
}
