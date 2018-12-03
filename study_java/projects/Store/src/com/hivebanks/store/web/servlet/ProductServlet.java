package com.hivebanks.store.web.servlet;

import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.Product;
import com.hivebanks.store.service.ProductService;
import com.hivebanks.store.service.serviceImp.ProductServiceImp;
import com.hivebanks.store.utils.UUIDUtils;
import com.hivebanks.store.web.base.BaseServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "ProductServlet")
public class ProductServlet extends BaseServlet {

    public String findProductsWithCidAndPage(HttpServletRequest request, HttpServletResponse response) throws Exception {
        int curNum = Integer.parseInt(request.getParameter("num"));
        String cid = request.getParameter("cid");
        ProductService productService = new ProductServiceImp();
        PageModel pm = productService.findProductsWithCidAndPage(cid, curNum);
        request.setAttribute("page", pm);
        return "/jsp/product_list.jsp";
    }


    public String findProductByPid(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String pid = request.getParameter("pid");
        ProductService productService = new ProductServiceImp();
        Product product = productService.findProductByPid(pid);

        request.setAttribute("pro", product);
        String ranStr = UUIDUtils.getId();
        request.getSession().setAttribute("ranStr", ranStr);
        System.out.println(ranStr);

        //转发到product_info.jsp
        return "/jsp/product_info.jsp";
    }
}
