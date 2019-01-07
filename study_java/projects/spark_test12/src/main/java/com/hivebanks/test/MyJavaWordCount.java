package com.hivebanks.test;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.function.FlatMapFunction;
import org.apache.spark.api.java.function.Function2;
import org.apache.spark.api.java.function.PairFunction;
import scala.Tuple2;

import java.util.Arrays;

/**
 * @Classname MyJavaWordCount
 * @Description TODO
 * @Date 2019/1/7 2:54 PM
 * @Created by pool
 */
public class MyJavaWordCount {
    public static void main(String[] args) {
        //检查参数
        if(args.length <2)
        {
            System.err.println("Usage: myjavawordcount <input> <output>");
            System.exit(1);
        }
        //获取参数
        String input = args[0];
        String output = args[1];

        //sparkcontext
        SparkConf sparkConf = new SparkConf().setAppName("MyJavaCount");
        JavaSparkContext sc = new JavaSparkContext(sparkConf);

        //获取相关数据
        JavaRDD<String> stringJavaRDD = sc.textFile(input);

        //进行计算
        JavaRDD<String> words = stringJavaRDD.flatMap(new FlatMapFunction<String, String>() {

            @Override
            public Iterable<String> call(String line) throws Exception {
                return Arrays.asList(line.split(" "));
            }
        });

        JavaPairRDD<String, Integer> result = words.mapToPair(new PairFunction<String, String, Integer>() {
            @Override
            public Tuple2<String, Integer> call(String word) throws Exception {
                return new Tuple2<>(word, 1);
            }
        }).reduceByKey(new Function2<Integer, Integer, Integer>() {
            @Override
            public Integer call(Integer x, Integer y) throws Exception {
                return x + y;
            }
        });
        //保存结果
        result.saveAsTextFile(output);

        //退出sc
        sc.stop();

    }
}
