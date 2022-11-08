### 将原有gitee仓库修改为github仓库并进行开发

1. 远程端：在github中选择导入仓库，填写gitee仓库地址导入即可

2. 本地端：

   1. 查看当前仓库名称并移除

      ```shell
      $git remote
      $git remote remove [origin]
      ```

   2. 重新链接新的github地址

      ```shell
      $git remote add [origin] [仓库地址]
      ```

   3. 进行一次同步

      ```shell
      $git pull
      ```

### 邀请开发者参与开发已有github仓库

