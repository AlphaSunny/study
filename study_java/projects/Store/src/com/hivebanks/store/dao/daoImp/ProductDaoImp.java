package com.hivebanks.store.dao.daoImp;

import com.hivebanks.store.dao.ProductDao;
import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.Product;
import com.hivebanks.store.utils.JDBCUtils;
import org.apache.commons.dbutils.DbUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;

import java.sql.SQLException;
import java.util.List;

public class ProductDaoImp implements ProductDao {

    @Override
    public List<Product> findNewProducts() throws SQLException {
        String sql = "select * from product where pflag = 0 order by pdate desc limit 0,9";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        return qr.query(sql, new BeanListHandler<Product>(Product.class));
    }

    @Override
    public List<Product> findHotProducts() throws SQLException {
        String sql = "select * from product where is_hot =1 and pflag=0 order by pdate desc limit 0,9";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        return qr.query(sql, new BeanListHandler<Product>(Product.class));
    }

    @Override
    public Product findProductByPid(String pid) throws SQLException {
        String sql = "select * from product where pid = ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        return qr.query(sql, new BeanHandler<Product>(Product.class), pid);
    }

    @Override
    public List<Product> findProductsWithCidAndPage(String cid, int startIndex, int pageSize) throws SQLException {
        String sql = "select * from product where cid = ? limit ?, ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        return qr.query(sql, new BeanListHandler<Product>(Product.class), cid, startIndex, pageSize);
    }


    @Override
    public void saveProduct(Product product) throws SQLException {
        String sql = "insert into product values (?,?,?,?,?,?,?,?,?,?)";
        Object[] params = {product.getPid(), product.getPname(), product.getMarket_price(), product.getShop_price(), product.getPimage(),
                            product.getPdate(), product.getIs_hot(), product.getPdesc(),product.getPflag(), product.getCid()};
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        qr.update(sql, params);
    }

    @Override
    public int findTotalNum(String cid) throws SQLException {
        String sql = "select count(*) from product where cid = ?";
        QueryRunner qr = new QueryRunner(JDBCUtils.getDataSource());
        Long num = (Long)qr.query(sql, new ScalarHandler(), cid);
        return num.intValue();
    }
}
