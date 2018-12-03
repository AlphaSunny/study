package com.hivebanks.store.web.servlet;

import com.hivebanks.store.domain.Cart;
import com.hivebanks.store.domain.CartItem;
import com.hivebanks.store.domain.Product;
import com.hivebanks.store.domain.User;
import com.hivebanks.store.service.ProductService;
import com.hivebanks.store.service.serviceImp.ProductServiceImp;
import com.hivebanks.store.web.base.BaseServlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "CartServlet")
public class CartServlet extends BaseServlet {
    public String addToCart(HttpServletRequest req, HttpServletResponse res) throws Exception
    {
        User user = (User) req.getSession().getAttribute("loginUser");
        if(null== user)
        {
            req.setAttribute("msg", "请登陆后购买商品");
            return "jsp/login.jsp";
        }

        String pid = req.getParameter("pid");
        int num = Integer.parseInt(req.getParameter("num"));
        ProductService productService = new ProductServiceImp();
        Product product = productService.findProductByPid(pid);
        CartItem item = new CartItem();
        item.setProduct(product);
        item.setNum(num);
        item.setSubTotal();

        Cart cart = (Cart) req.getSession().getAttribute("cart");
        if(cart==null)
        {
            cart = new Cart();
            req.getSession().setAttribute("cart", cart);
        }

        cart.addCart(item);
        res.sendRedirect(req.getContextPath() + "/jsp/cart.jsp");

        return null;

    }

}
