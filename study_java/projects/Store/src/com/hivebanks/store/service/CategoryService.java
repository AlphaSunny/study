package com.hivebanks.store.service;

import com.hivebanks.store.domain.Category;

import java.sql.SQLException;
import java.util.List;

public interface CategoryService {
    List<Category> findAllCats()throws SQLException;

    void saveCat(Category c)throws SQLException;
}
