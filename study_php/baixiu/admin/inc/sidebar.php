<div class="aside">
    <div class="profile">
        <img class="avatar" src="/../uploads/avatar.jpg">
        <h3 class="name">布头儿</h3>
    </div>
    <ul class="nav">
        <li<?php echo strstr($_SERVER["PHP_SELF"], 'index') ? ' class ="active"': ''?>>
            <a href="index.php"><i class="fa fa-dashboard"></i>仪表盘</a>
        </li>

        <li<?php echo in_array(explode('/', $_SERVER["PHP_SELF"])[2], array('posts.php', 'post-add.php', 'categories.php')) ? ' class ="active"': ''?>>
            <a href="#menu-posts" <?php echo in_array(explode('/', $_SERVER["PHP_SELF"])[2], array('posts.php', 'post-add.php', 'categories.php')) ? '' :' class ="collapsed"'?> data-toggle="collapse">
                <i class="fa fa-thumb-tack"></i>文章<i class="fa fa-angle-right"></i>
            </a>
            <ul id="menu-posts" class="collapse <?php echo in_array(explode('/', $_SERVER["PHP_SELF"])[2], array('posts.php', 'post-add.php', 'categories.php')) ? ' in' :''?>">
                <li<?php echo strstr($_SERVER["PHP_SELF"], 'posts') ? ' class ="active"': ''?>><a href="posts.php">所有文章</a></li>
                <li<?php echo strstr($_SERVER["PHP_SELF"], 'post-add') ? ' class ="active"': ''?>><a href="post-add.php">写文章</a></li>
                <li<?php echo strstr($_SERVER["PHP_SELF"], 'categories') ? ' class ="active"': ''?>><a href="categories.php">分类目录</a></li>
            </ul>
        </li>
        <li<?php echo strstr($_SERVER["PHP_SELF"], 'comments') ? ' class ="active"': ''?>>
            <a href="comments.php"><i class="fa fa-comments"></i>评论</a>
        </li>
        <li<?php echo strstr($_SERVER["PHP_SELF"], 'users') ? ' class ="active"': ''?>>
            <a href="users.php"><i class="fa fa-users"></i>用户</a>
        </li>
        <li<?php echo in_array(explode('/', $_SERVER["PHP_SELF"])[2], array('nav-menus.php', 'slides.php', 'settings.php')) ? ' class ="active"': ''?>>
            <a href="#menu-settings" data-toggle="collapse" <?php echo in_array(explode('/', $_SERVER["PHP_SELF"])[2], array('nav-menus.php', 'slides.php', 'settings.php')) ? '':' class ="collapsed"'?>>
                <i class="fa fa-cogs"></i>设置<i class="fa fa-angle-right"></i>
            </a>
            <ul id="menu-settings" class="collapse <?php echo in_array(explode('/', $_SERVER["PHP_SELF"])[2], array('nav-menus.php', 'slides.php', 'settings.php')) ? ' in':''?>"  >
                <li<?php echo strstr($_SERVER["PHP_SELF"], 'nav-menus') ? ' class ="active"': ''?>><a href="nav-menus.php">导航菜单</a></li>
                <li<?php echo strstr($_SERVER["PHP_SELF"], 'slides') ? ' class ="active"': ''?>><a href="slides.php">图片轮播</a></li>
                <li<?php echo strstr($_SERVER["PHP_SELF"], 'settings') ? ' class ="active"': ''?>><a href="settings.php">网站设置</a></li>
            </ul>
        </li>
    </ul>
</div>