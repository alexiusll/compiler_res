## 🟦 命令行参考

需要在 build 文件夹下执行

```shell
# 在 build 文件夹下执行

# 构建项目: 
cmake ..
# 构建项目(不使用自建函数): 
cmake .. -DUSE_MYMATH=OFF
# 编译: 
cmake --build .
# 编译: 使用 Release
cmake --build . --config Release 

# 安装指令:
# 此步骤将安装适当的头文件、库和可执行文件
cmake --install .
# 对于多配置工具，不要忘记使用 --config参数来指定配置。
cmake --install . --config Release
# 如果使用 IDE，只需构建INSTALL目标即可。您可以从命令行构建相同的安装目标，如下所示：
cmake --build . --target install --config Debug
# CMake 变量CMAKE_INSTALL_PREFIX用于确定文件安装位置的根目录。如果使用该 命令，可以通过参数覆盖安装前缀 。
# 例如：cmake --install--prefix
cmake --install . --prefix "/home/myuser/installdir"

# 测试指令:
# 先进行构建，之后再运行测试用例
# 表示查询测试列表而不实际运行测试。
ctest -N
# -C Debug选项：表示指定要运行的构建配置。
# --- 在这里，指定了构建配置为Debug。对于多配置生成器（如Visual Studio），这样可以选择在Debug模式下运行测试。
# -VV选项：表示输出更详细的测试执行信息。
# --- 通过这个选项，ctest会输出更多关于测试运行情况的信息，包括测试的名称、执行时间、是否通过等等。
ctest -C Debug -VV

```

