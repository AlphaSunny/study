package com.hivebanks.store.web.servlet;

import com.hivebanks.store.domain.Category;
import com.hivebanks.store.domain.Product;
import com.hivebanks.store.service.CategoryService;
import com.hivebanks.store.service.ProductService;
import com.hivebanks.store.service.serviceImp.CategoryServiceImp;
import com.hivebanks.store.service.serviceImp.ProductServiceImp;
import com.hivebanks.store.web.base.BaseServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.List;


public class IndexServlet extends BaseServlet {

    @Override
    public String execute(HttpServletRequest req, HttpServletResponse res) throws Exception {
        CategoryService CategoryService=new CategoryServiceImp();
        List<Category> list=CategoryService.findAllCats();
        //放入request域对象
        req.setAttribute("allCats", list);

        ProductService ProductService=new ProductServiceImp();
        //获取最新9件商品
        List<Product> list01=ProductService.findNewProducts();
        //获取最热9件商品
        List<Product> list02=ProductService.findHotProducts();

        //将最新商品放入request
        req.setAttribute("news", list01);
        //将最热商品放入request
        req.setAttribute("hots", list02);

        return "/jsp/index.jsp";
    }
}
