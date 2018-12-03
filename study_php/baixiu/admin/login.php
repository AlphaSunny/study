<?php

      function login() {
        if(empty($_POST['username']) || empty($_POST['password']))
        {
            $message = "please input the username and password";
        } else
        {
            $username = $_POST['username'];
            $password = $_POST['password'];
            if($username==='admin@gmail' && $password==='admin')
            {
                header("Location:/admin/index.php");
                exit;
            } else {
                $message = "wrong user name";
            }
        }
    }
    if($_SERVER['REQUEST_METHOD'] === 'POST') {
        login();
    }

?>

<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="utf-8">
  <title>Sign in &laquo; Admin</title>
  <link rel="stylesheet" href="/assets/vendors/bootstrap/css/bootstrap.css">
  <link rel="stylesheet" href="/assets/css/admin.css">
</head>
<body>
  <div class="login">
    <form class="login-wrap" action="<?php $_SERVER["PHP_SELF"]?>" method="post">
      <img class="avatar" src="/assets/img/default.png">
        <?php if(isset($message)): ?>>
            <div class="alert alert-danger">
                <strong>wrong! </strong><?php echo $message?>
            </div>
        <?php endif; ?>

      <div class="form-group">
        <label for="email" class="sr-only">邮箱</label>
        <input id="email" type="email" name="username" class="form-control" placeholder="邮箱" autofocus>
      </div>
      <div class="form-group">
        <label for="password" class="sr-only">密码</label>
        <input id="password" name="password" type="password" class="form-control" placeholder="密码">
      </div>
      <button class="btn btn-primary btn-block" type="submit">登 录</button>
    </form>
  </div>
    <script src="/assets/vendors/jquery/jquery.js"></script>
    <script>
        $(function ($) {
            var emailFormat = /^[a-zA-Z0-9_.-]+@[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*\.[a-zA-Z0-9]{2,6}$/;
            $('#email').on('blur', function () {
                var value = $(this).val();
                if(!value || !emailFormat.test(value)) return;
                $.get('/admin/api/avatar.php', {email: value}, function (res) {
                    if(!res) return;
                    $('.avatar').fadeOut(function () {
                        $(this).on('load', function () {
                            $(this).fadeIn();
                        }).attr('src', res);
                    })
                })
            })

        })
    </script>
</body>
</html>
