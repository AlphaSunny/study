package com.hivebanks.store.service.serviceImp;

import com.hivebanks.store.dao.CategoryDao;
import com.hivebanks.store.domain.Category;
import com.hivebanks.store.service.CategoryService;
import com.hivebanks.store.utils.BeanFactory;

import java.sql.SQLException;
import java.util.List;

public class CategoryServiceImp implements CategoryService {

    CategoryDao categoryDao = (CategoryDao) BeanFactory.createObject("CategoryDao");

    @Override
    public List<Category> findAllCats() throws SQLException {
        return categoryDao.findAllCats();
    }

    @Override
    public void saveCat(Category c) throws SQLException {
        categoryDao.saveCat(c);
    }
}
