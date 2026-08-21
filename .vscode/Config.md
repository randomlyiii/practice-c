# C 文件编译与运行配置

本目录使用 VS Code 的 `F5` 自动编译并运行当前打开的 C 文件。

## 文件说明

- `tasks.json`：定义 F5 前执行的编译任务。
- `launch.json`：定义 F5 的运行方式。
- `build-all.ps1`：执行增量编译和缓存判断。
- `current.build.json`：记录上一次编译的源文件和内容哈希。
- `current.exe`：当前 C 文件生成的可执行文件，位于当前 `.c` 文件所在目录。

## F5 执行流程

按下 `F5` 后，执行以下流程：

1. 获取当前 VS Code 编辑器打开的 `.c` 文件名。
2. 检查该文件是否存在。
3. 计算当前 C 文件内容的 SHA-256 哈希值。
4. 对比上一次记录的源文件路径和哈希值。
5. 如果文件内容没有变化，并且 `current.exe` 存在，则跳过 GCC 编译。
6. 如果文件发生变化、切换了 C 文件，或者 `current.exe` 不存在，则重新编译。
7. 编译结果保存为当前 C 文件目录下的 `current.exe`。
8. 编译成功后打开独立的 cmd 窗口运行 `current.exe`。
9. 程序运行结束后显示输出，并等待按键关闭 cmd 窗口。

## 输出示例

假设当前文件是：

```text
D:\work\C-practice\DegreeEasy-合并两个有序数组.c
```

生成的文件是：

```text
D:\work\C-practice\current.exe
```

如果 C 文件位于子目录，则 `current.exe` 会生成在对应的子目录中。

## 编译命令

实际使用的 GCC 参数为：

```text
gcc -g -Wall -Wextra 源文件.c -o current.exe
```

参数说明：

- `-g`：生成调试信息。
- `-Wall`：启用常见警告。
- `-Wextra`：启用额外警告。
- `-o current.exe`：指定输出文件名。

## 增量编译规则

以下情况会重新生成并覆盖 `current.exe`：

- 第一次按 `F5`。
- 修改当前 `.c` 文件内容。
- 切换到另一个 `.c` 文件。
- 删除当前目录下的 `current.exe`。
- 删除 `.vscode/current.build.json`。

以下情况会跳过编译：

- 当前 `.c` 文件路径没有变化。
- 当前 `.c` 文件内容没有变化。
- 当前目录下的 `current.exe` 仍然存在。

注意：即使只是增加空格、换行或注释，只要文件内容发生变化，也会重新编译。

## cmd 窗口行为

F5 使用 Windows 命令提示符运行程序：

```text
cmd.exe /d /c current.exe & pause
```

程序结束后，窗口会停留并显示输出。按回车或任意键后，cmd 窗口关闭。

## 常见问题

### 找不到 GCC

请确认 GCC 已安装，并且 `gcc` 已加入系统的 `PATH` 环境变量。

### 找不到 GDB

`launch.json` 使用了 `gdb.exe`。请确认 GDB 已安装，并且 `gdb.exe` 已加入系统的 `PATH` 环境变量。

### 出现 unused parameter 警告

这是 GCC 的警告，表示函数参数已声明但没有使用。警告通常不会阻止程序生成和运行 exe。

### 修改了代码但没有重新编译

请确认文件已经保存。脚本根据磁盘中的文件内容计算哈希值，未保存的编辑内容不会参与编译。
