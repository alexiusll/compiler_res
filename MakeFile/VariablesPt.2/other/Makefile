#* 🟦 命令行参数和重写
#* 您可以使用override关键字覆盖来自命令行的变量。
#* 在这里，我们通过在命令行中运行make并传入选项option_one=hi来覆盖变量。

# # Overrides command line arguments
# override option_one ?= did_override
# # Does not override command line arguments
# option_two = not_override
# all: 
# 	@echo $(option_one)
# 	@echo $(option_two)

#* 🟦 命令列表和定义
#* define指令不是一个函数，尽管它可能看起来像是一个函数。
#* 我见过它被很少使用，所以我不会详细解释，但它主要用于定义预定义的配方，并与eval函数配合使用效果较好。
#* define/endef仅仅是创建一个变量，该变量被设置为一组命令。
#* 请注意，它与在命令之间使用分号有些不同，因为每个命令在单独的Shell中运行，正如预期的那样。
#TODO： 这个代码无法正常运行

# one = export blah="I was set!"; echo $$blah

# define two
# export blah="I was set!"
# echo $$blah
# endef

# all: 
# 	@echo "This prints 'I was set'"
# 	@$(one)
# 	@echo "This does not print 'I was set' because each command runs in a separate shell"
# 	@$(two)

#* 🟦 特定目标的变量
#* 可以为特定目标设置变量

# a: one = cool
# all: a other

# a: 
# 	echo one is defined: $(one)

# other:
# 	echo one is nothing: $(one)

#* 🟦 模式特定变量
#* 您可以为特定目标模式设置变量。

%.c: one = cool
all: blah.c other

blah.c: 
	echo one is defined: $(one)

other:
	echo one is nothing: $(one)