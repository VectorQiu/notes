> [Pro Git](https://git-scm.com/book/en/v2)

`git submodule` 是 Git 中用于管理嵌入式仓库的工具。通过子模块，你可以在一个 Git 仓库中包含另一个独立的 Git 仓库。以下是常用的 `git submodule` 操作及其解释：

### 1. 添加子模块

要在项目中添加一个子模块，可以使用以下命令：

```bash
git submodule add <repository_url> <path>
```

- `<repository_url>`：子模块的 Git 仓库地址。
- `<path>`：子模块在主项目中的路径。

例如：

```bash
git submodule add https://github.com/example/repo.git libs/repo
```

这个命令会将 `repo` 仓库添加为当前项目中的子模块，放置在 `libs/repo` 目录下。

### 2. 初始化子模块

如果你克隆了一个包含子模块的仓库，子模块的内容不会自动下载。你需要运行以下命令来初始化和更新子模块：

```bash
git submodule update --init --recursive
```

这会初始化并更新仓库中所有子模块及其子模块。

### 3. 更新子模块

要更新子模块以获取其最新的提交，可以使用：

```bash
git submodule update --remote --merge
```

- `--remote`：拉取子模块的最新提交。
- `--merge`：将子模块的最新提交与当前的子模块分支合并。

### 4. 移除子模块

要从项目中移除子模块，需要进行以下几个步骤：

1. 删除子模块在 

   ```
   .gitmodules
   ```

    文件中的配置：

   ```bash
   git config -f .gitmodules --remove-section submodule.<path>
   ```

2. 删除子模块相关的 Git 配置：

   ```bash
   git config -f .git/config --remove-section submodule.<path>
   ```

3. 从索引中移除子模块的追踪：

   ```bash
   git rm --cached <path>
   ```

4. 删除子模块的实际目录：

   ```bash
   rm -rf <path>
   ```

5. 删除 

   ```bash
   .git/modules/<path>
   ```

    目录中的子模块信息：

   ```bash
   rm -rf .git/modules/<path>
   ```

### 5. 同步子模块

有时候，主项目中的子模块路径会发生变化，或子模块的 URL 会被修改。这时需要同步子模块：

```bash
git submodule sync --recursive
```

### 6. 查看子模块的状态

你可以查看子模块的当前状态：

```bash
git submodule status
```

这个命令会列出每个子模块的当前提交、路径和状态（如已修改但未提交的变化）。

### 总结

Git 子模块是一个非常强大的工具，允许你在一个项目中包含和管理多个独立的 Git 仓库。在使用子模块时，注意同步、更新和初始化子模块，以确保主项目与其子模块之间的一致性。