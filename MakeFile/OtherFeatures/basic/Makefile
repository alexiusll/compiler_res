#* 🟦 vpath 指令
#* 使用vpath指令可以指定一组前置条件存在的位置。
#* 其格式为：vpath <模式> <目录，使用空格或冒号分隔>。
#* 其中，<模式> 可以包含 % 符号，用于匹配零个或多个字符。
#* 你也可以使用变量VPATH来实现类似的全局效果。

# vpath %.h ../headers ../other-directory

# # 注意: vpath 允许找到 blah.h，尽管 blah.h 从未出现在工作目录中
# some_binary: ../headers blah.h
# 	touch some_binary

# ../headers:
# 	mkdir ../headers

# # 我们调用目标 blah.h 而不是. ./headers/blah.h，因为这是 some _ binary 正在寻找的前置条件
# # 通常，blah.h已经存在，您不需要这个。
# blah.h:
# 	touch ../headers/blah.h

# clean:
# 	rm -rf ../headers
# 	rm -f some_binary

#* 🟦 多行
#* 反斜杠（"\"）字符允许我们在命令过长时使用多行来表达。

# some_file: 
# 	echo This line is too long, so \
# 		it is broken up into multiple lines

#* 🟦 .phony
#* 为一个目标添加 .PHONY 会防止Make将伪目标与文件名混淆。
#* 在这个例子中，如果创建了名为 clean 的文件，执行 make clean 时仍然会运行相应的规则。
#* 从技术上讲，我应该在每个使用 all 或 clean 的示例中都加上 .PHONY，但为了保持示例的简洁性，
#* 我没有这样做。另外，"phony"（伪目标）通常具有很少作为文件名出现的名称，在实践中，许多人会忽略添加 .PHONY。

# some_file:
# 	echo "23333">some_file
# 	echo "666">clean

# .PHONY: clean
# clean:
# 	del some_file
# 	del clean

#* 🟦 .delete_on_error
#* 如果一个命令返回非零的退出状态，make工具将停止运行该规则（并向前传递到前置条件）。
#* 使用DELETE_ON_ERROR选项，如果一个规则以此方式失败，将会删除该规则的目标文件。
#* 这将适用于所有目标，而不仅仅是像.PHONY这样的目标。
#* 尽管出于历史原因make工具默认不会启用此选项，但总体上来说，始终使用这个选项是个好主意。

.DELETE_ON_ERROR:
all: one two

one:
	echo "23333" > one

two:
	echo "23333" > two
	false