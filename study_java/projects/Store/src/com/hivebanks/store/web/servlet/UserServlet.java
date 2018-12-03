package com.hivebanks.store.web.servlet;

import com.hivebanks.store.domain.User;
import com.hivebanks.store.service.UserService;
import com.hivebanks.store.utils.BeanFactory;
import com.hivebanks.store.utils.CookUtils;
import com.hivebanks.store.utils.MyBeanUtils;
import com.hivebanks.store.utils.UUIDUtils;
import com.hivebanks.store.web.base.BaseServlet;

import javax.servlet.ServletException;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class UserServlet extends BaseServlet {
    UserService userService = (UserService) BeanFactory.createObject("UserService");


    //loginUI
    public String registUI(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        return "/jsp/register.jsp";
    }

    //registUI
    public String loginUI(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        Cookie ck = CookUtils.getCookieByName("remUser", request.getCookies());
        if(null!= ck)
            request.setAttribute("remUser", ck.getValue());

        return "/jsp/login.jsp";
    }

    //loginUI
    public String userLogin(HttpServletRequest request, HttpServletResponse response) throws Exception {
        User user01 = MyBeanUtils.populate(User.class, request.getParameterMap());
        User user02 = userService.userLogin(user01);

        if(null!=user02){
            //登录成功,向session中放入用户信息,重定向到首页
            request.getSession().setAttribute("loginUser",user02);

            //在登录成功的基础上,判断用户是否选中自动登录复选框
            String autoLogin=request.getParameter("autoLogin");
            if("yes".equals(autoLogin)){
                //用户选中自动登录复选框
                Cookie ck=new Cookie("autoLogin",user02.getUsername()+"#"+user02.getPassword());
                ck.setPath("/store_v4");
                ck.setMaxAge(23423424);
                response.addCookie(ck);
            }
            //remUser
            String remUser=request.getParameter("remUser");
            if("yes".equals(remUser)){
                //用户选中自动登录复选框
                Cookie ck=new Cookie("remUser",user02.getUsername());
                ck.setPath("/store_v4");
                ck.setMaxAge(23423424);
                response.addCookie(ck);
            }
            response.sendRedirect(request.getContextPath()+"/index.jsp");
        }else{
            //登录失败,向request放入提示信息,转发到登录页面,显示提示userLogin
            request.setAttribute("msg", "用户名和密码不匹配!");
            return "/jsp/login.jsp";
        }
        return null;
    }

    /**
     * @dev:logout 1.清session  2.清cookie
     * @param request
     * @param response
     * @return
     * @throws ServletException
     * @throws IOException
     */
    public String logOut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        request.getSession().invalidate();
        Cookie ck = CookUtils.getCookieByName("autoLogin", request.getCookies());
        if(null!=ck)
        {
            ck.setMaxAge(0);
            ck.setPath("/store_v4");
            response.addCookie(ck);
        }
        response.sendRedirect(request.getContextPath() + "/IndexServlet");
        return null;
    }

    /**
     * @dev:logout 1.清session  2.清cookie
     * @param request
     * @param response
     * @return
     * @throws ServletException
     * @throws IOException
     */
    public String userRegist(HttpServletRequest request, HttpServletResponse response) throws Exception {
        User user = MyBeanUtils.populate(User.class, request.getParameterMap());
        user.setUid(UUIDUtils.getId());
        user.setState(0);
        user.setCode(UUIDUtils.getId());
        userService.userRegist(user);

        request.setAttribute("msg", "用户注册成功,请激活!");
        return  "/jsp/info.jsp";
    }

    public String userExists(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String name = request.getParameter("username");
        User user = userService.findUserByUserName(name);

        if(user!=null)
        {
            response.getWriter().print("11");
        } else {
            response.getWriter().print("00");
        }
        return null;
    }





}
