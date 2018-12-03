package com.hivebanks.store.web.base;

import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.lang.reflect.Method;

@WebServlet(name = "BaseServlet")
public class BaseServlet extends HttpServlet {
    @Override
    public void service(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException
    {
        String md = req.getParameter("method");
        if(md==null || "".equals(md) || md.trim().equals(""))
            md = "execute";

        Class clazz = this.getClass();
        try {
            Method method = clazz.getMethod(md, HttpServletRequest.class, HttpServletResponse.class);
            if(null != method)
            {
                String path = (String)method.invoke(this, req, res);
                if(null!= path)
                    req.getRequestDispatcher(path).forward(req, res);
            }
        } catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public String execute(HttpServletRequest req, HttpServletResponse res) throws Exception
    {
        return null;
    }
}
