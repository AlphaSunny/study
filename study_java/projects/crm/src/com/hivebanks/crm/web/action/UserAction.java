package com.hivebanks.crm.web.action;

import com.hivebanks.crm.domain.User;
import com.hivebanks.crm.service.UserService;
import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

/**
 * @Classname UserAction
 * @Description TODO
 * @Date 2018/11/29 4:04 PM
 * @Created by pool
 */
public class UserAction extends ActionSupport implements ModelDriven<User> {

    //模型驱动
    private User user = new User();
    @Override
    public User getModel() {
        return user;
    }

    //注入service
    private UserService userService;

    public void setUserService(UserService userService) {
        this.userService = userService;
    }

    public String regist(){
        userService.regist(user);
        return LOGIN;
    }

    public String login()
    {
        User existUser = userService.login(user);
        if(existUser == null)
        {
            this.addActionError("the user is not exist");
            return LOGIN;
        }else
        {
            ActionContext.getContext().getSession().put("existUser", existUser);
            return SUCCESS;
        }
    }


}
