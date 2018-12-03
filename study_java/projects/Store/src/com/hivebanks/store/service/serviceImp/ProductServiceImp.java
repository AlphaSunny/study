package com.hivebanks.store.service.serviceImp;

import com.hivebanks.store.dao.ProductDao;
import com.hivebanks.store.dao.daoImp.ProductDaoImp;
import com.hivebanks.store.domain.PageModel;
import com.hivebanks.store.domain.Product;
import com.hivebanks.store.service.ProductService;

import java.sql.SQLException;
import java.util.List;

public class ProductServiceImp implements ProductService {

    ProductDao productDao = new ProductDaoImp();


    @Override
    public List<Product> findNewProducts() throws SQLException {
        return productDao.findNewProducts();
    }

    @Override
    public List<Product> findHotProducts() throws SQLException {
        return productDao.findHotProducts();
    }

    @Override
    public Product findProductByPid(String pid) throws SQLException {
        Product pro = productDao.findProductByPid(pid);
        return pro;
    }

    @Override
    public PageModel findProductsWithCidAndPage(String cid, int curNum) throws SQLException {
        int totalRecords = productDao.findTotalNum(cid);
        PageModel pm = new PageModel(curNum, totalRecords, 12);
        List<Product> list = productDao.findProductsWithCidAndPage(cid, pm.getStartIndex(), pm.getPageSize());
        pm.setList(list);
        pm.setUrl("ProductServlet?method=findProductsWithCidAndPage&cid="+cid);
        return pm;
    }

    @Override
    public void saveProduct(Product product) throws SQLException {
        productDao.saveProduct(product);
    }
}
