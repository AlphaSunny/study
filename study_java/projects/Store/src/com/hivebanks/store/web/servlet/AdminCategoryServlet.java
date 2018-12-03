package com.hivebanks.store.web.servlet;

import com.hivebanks.store.domain.Category;
import com.hivebanks.store.service.CategoryService;
import com.hivebanks.store.service.serviceImp.CategoryServiceImp;
import com.hivebanks.store.web.base.BaseServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;

@WebServlet(name = "AdminCategoryServlet")
public class AdminCategoryServlet extends BaseServlet {
    CategoryService categoryService = new CategoryServiceImp();

    public String findAllCats(HttpServletRequest request, HttpServletResponse response) throws Exception {
        List<Category> allCats = categoryService.findAllCats();
        request.setAttribute("allCats", allCats);
        return "/admin/category/list.jsp";
    }

    //addCatUI
    public String addCatUI(HttpServletRequest request, HttpServletResponse response) throws Exception {
        return "/admin/category/add.jsp";

    }



}
