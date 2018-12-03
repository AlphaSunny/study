package com.hivebanks.tx.demo1;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import javax.annotation.Resource;

/**
 * @Classname SpringDemo1
 * @Description TODO
 * @Date 2018/11/26 2:19 PM
 * @Created by pool
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("classpath:tx.xml")
public class SpringDemo1 {
    @Resource(name = "accountService")
    private AccountService accountService;



    @Test
    public void demo1() {
        accountService.transfer("yang", "xu", 100d);
    }
}
