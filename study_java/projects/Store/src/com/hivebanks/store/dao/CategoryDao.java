package com.hivebanks.store.dao;

import com.hivebanks.store.domain.Category;

import java.sql.SQLException;
import java.util.List;

public interface CategoryDao {
    List<Category> findAllCats()throws SQLException;

    void saveCat(Category c)throws SQLException;
}
