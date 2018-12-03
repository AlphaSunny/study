package com.hivebanks.tx.demo3;

import com.hivebanks.tx.demo2.AccountService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import javax.annotation.Resource;

/**
 * @Classname SpringDemo1
 * @Description TODO
 * @Date 2018/11/26 3:02 PM
 * @Created by pool
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("classpath:tx3.xml")
public class SpringDemo1 {

    @Resource(name = "accountService")
    private AccountService accountService;



    @Test
    public void demo1() {
        accountService.transfer("yang", "xu", 100d);
    }
}
