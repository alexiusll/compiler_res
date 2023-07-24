#* 变量有两种类型：
#* ◼ 递归类型（使用=）- 只有在使用命令时才会查找变量，而不是在定义时。
#* ◼ 简单展开类型（使用:=）- 像普通的命令式编程一样，只有到 目前为止 定义的变量会被展开。

#* ===== 代码1 =====
# # 递归变量。这将在下面“稍后”打印
# one = one ${later_variable}
# # 简单展开变量。这将不会在下面“稍后”打印
# two := two ${later_variable}
# later_variable = later
# all: 
# 	echo $(one)
# 	echo $(two)
#* ===== 代码1 结束 =====

#* 简单展开类型（使用:=）允许您对变量进行追加。递归定义将导致无限循环错误。

# #* ===== 代码2 =====
# one = hello
# # one gets defined as a simply expanded variable (:=) and thus can handle appending
# one := ${one} there

# all: 
# 	echo $(one)
# #* ===== 代码2 结束 =====

#* ?= 只在变量尚未被设置时才会设置变量的值。

# #* ===== 代码3 =====
# one = hello
# one ?= will not be set
# two ?= will be set

# all: 
# 	echo $(one)
# 	echo $(two)
# #* ===== 代码3 结束 =====

#* 在一行末尾的空格不会被去除，但位于行首的空格会被去除。
#* 要创建一个只包含单个空格的变量，可以使用$(nullstring)。

# #* ===== 代码4 =====
# with_spaces = hello   # with_spaces has many spaces after "hello"
# after = $(with_spaces)there

# nullstring =
# space = $(nullstring) # Make a variable with a single space.

# all: 
# 	echo "$(after)"
# 	echo start"$(space)"end
# #* ===== 代码4 结束=====

#* 未定义的变量实际上是一个空字符串！

# #* ===== 代码5 =====
# # Undefined variables are just empty strings!
# all: 
# 	echo $(nowhere)
# #* ===== 代码5 结束 =====

#* 使用+=附加

#* ===== 代码6 =====
foo := start
foo += more

all: 
	echo $(foo)
#* ===== 代码6 结束 =====