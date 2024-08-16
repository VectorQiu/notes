## 问题描述

vscode 终端不能使用命令

## 解决方案

1. 以管理员身份运行VSCODE

2. 在终端执行命令，查看脚本执行策略

   显示内容为 `Restricted` 这个表示禁止终端使用命令的意思

   ```powershell
   PS C:\xxx\xxx> Get-ExecutionPolicy
   RemoteSigned
   ```

3. 在终端执行命令，设置为允许在终端运行命令

   ```powershell
   PS C:\xxx\xxx> Set-ExecutionPolicy RemoteSigned
   ```

   

