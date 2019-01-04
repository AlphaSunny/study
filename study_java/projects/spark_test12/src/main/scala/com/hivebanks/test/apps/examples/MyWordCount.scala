package com.hivebanks.test.apps.examples

import org.apache.spark.{SparkConf, SparkContext}

/**
  * @Classname MyWordCount
  * @Description TODO
  * @Date 2019/1/4 2:30 PM
  * @Created by pool
  */
object MyWordCount {
  def main(args: Array[String]): Unit = {
    //参数检查
    if (args.length <2)
      {
        System.err.print("Usage: MyWordCount <input> <output>")
        System.exit(1)
      }
    // 获取参数
    val input = args(0)
    val output = args(1)

    val conf = new SparkConf().setAppName("myWordCount")
    val sc = new SparkContext(conf)

    //读取数据
    val lines = sc.textFile(input)
    lines.flatMap(_.split( " ")).map((_,1)).reduceByKey(_+_).collect().foreach(println)

    //保存结果


    sc.stop()
  }

}
