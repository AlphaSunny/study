package com.hivebanks.crm.web.action;

import com.hivebanks.crm.domain.BaseDict;
import com.hivebanks.crm.service.BaseDictService;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;
import net.sf.json.JSONArray;
import net.sf.json.JsonConfig;
import org.apache.struts2.ServletActionContext;


import javax.servlet.ServletContext;
import java.io.IOException;
import java.util.List;

/**
 * @Classname BaseDictAction
 * @Description TODO
 * @Date 2018/12/3 1:58 PM
 * @Created by pool
 */
public class BaseDictAction extends ActionSupport implements ModelDriven<BaseDict> {

    private BaseDict baseDict = new BaseDict();
    @Override
    public BaseDict getModel() {
        return null;
    }

    private BaseDictService baseDictService;

    public void setBaseDictService(BaseDictService baseDictService) {
        this.baseDictService = baseDictService;
    }

    public String findByTypeCode() throws IOException
    {
        System.out.println("BaseDictAction中的findByTypeCode方法执行了");
        List<BaseDict> list = baseDictService.findByTypeCode(baseDict.getDict_type_code());
        JsonConfig jsonConfig = new JsonConfig();
        jsonConfig.setExcludes(new String[]{"dict_sort", "dict_enable" , "dict_memo"});
        JSONArray jsonArray = JSONArray.fromObject(list, jsonConfig );
        System.out.println(jsonArray.toString());

        ServletActionContext.getResponse().setContentType("text/html");
        ServletActionContext.getResponse().getWriter().println(jsonArray.toString());
        return NONE;
    }

}
