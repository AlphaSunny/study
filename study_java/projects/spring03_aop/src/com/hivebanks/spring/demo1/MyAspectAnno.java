package com.hivebanks.spring.demo1;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;

/**
 * @Classname MyAspectAnno
 * @Description TODO
 * @Date 2018/11/27 11:48 AM
 * @Created by pool
 */

@Aspect
public class MyAspectAnno {
    @Before(value = "MyAspectAnno.pointcut2()")
    public void before()
    {
        System.out.println("Before strengthen");
    }

    @AfterReturning(value = "MyAspectAnno.pointcut4()", returning = "result")
    public void afterReturning(Object result)
    {
        System.out.println("after strengthen" + result);
    }

    @Around(value = "MyAspectAnno.pointcut3()")
    public Object around(ProceedingJoinPoint point) throws Throwable
    {
        System.out.println("before proceed");
        Object obj = point.proceed();
        System.out.println("after proceed");
        return obj;
    }

    //异常抛出
    @AfterThrowing(value = "MyAspectAnno.pointcut1()", throwing = "e")
    public void afterThrowing(Throwable e)
    {
        System.out.println("After throwing" + e);
    }


    //最终通知
    @After(value = "MyAspectAnno.pointcut1()")
    public void after()
    {
        System.out.println("after .....");
    }



    //切入点注解
    @Pointcut( value = "execution(* com.hivebanks.spring.demo1.OrderDao.find(..))")
    private void pointcut1(){}
    @Pointcut( value = "execution(* com.hivebanks.spring.demo1.OrderDao.save(..))")
    private void pointcut2(){}
    @Pointcut( value = "execution(* com.hivebanks.spring.demo1.OrderDao.update(..))")
    private void pointcut3(){}
    @Pointcut( value = "execution(* com.hivebanks.spring.demo1.OrderDao.delete(..))")
    private void pointcut4(){}

}
