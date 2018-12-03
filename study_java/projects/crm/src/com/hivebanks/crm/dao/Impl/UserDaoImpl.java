package com.hivebanks.crm.dao.Impl;

import com.hivebanks.crm.dao.UserDao;
import com.hivebanks.crm.domain.User;
import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import java.util.List;

/**
 * @Classname UserDaoImpl
 * @Description TODO
 * @Date 2018/11/29 4:11 PM
 * @Created by pool
 */
public class UserDaoImpl extends HibernateDaoSupport implements UserDao {
    @Override
    public void save(User user) {
        this.getHibernateTemplate().save(user);
    }

    @Override
    public User login(User user) {
        List<User> list = (List<User>) this.getHibernateTemplate().find("from User where user_code = ? and  user_password= ?", user.getUser_code(), user.getUser_password());
        if(list.size() > 0)
        {
            return list.get(0);
        }
        return null;
    }

}
