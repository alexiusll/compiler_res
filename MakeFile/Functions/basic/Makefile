#* 🟦 第一个函数
#* 函数主要用于文本处理。使用 $(fn，参数)或 ${ fn，参数}调用函数。
#* Make 有大量的内置功能。

# bar := ${subst not, totally, "I am not superman"}
# all: 
# 	@echo $(bar)

#* 如果要替换空格或逗号，请使用变量

# comma := ,
# empty:=
# space := $(empty) $(empty)
# foo := a b c
# bar := $(subst $(space),$(comma),$(foo))

# all: 
# 	@echo $(bar)

#* 在函数的第一个参数后不要包含空格。否则，空格将被视为参数的一部分。

# comma := ,
# empty:=
# space := $(empty) $(empty)
# foo := a b c
# bar := $(subst $(space), $(comma) , $(foo))

# all: # Output is ", a , b , c". Notice the spaces introduced
# 	@echo $(bar)

#* 🟦 字符串替换
#* $(patsubst pattern,replacement,text) 是一个GNU Make中的函数，它的功能如下：

#* "在文本中查找与模式匹配的以空格分隔的单词，并用替换文本进行替换。在模式中，可以包含一个‘%’作为通配符，匹配单词内的任意数量的任意字符。
#* 如果替换文本中也包含‘%’，那么‘%’将被替换为模式中匹配的文本。在模式和替换文本中，只有第一个‘%’会被这样处理；后续的‘%’将保持不变。" (GNU文档)

#* 替换引用$(text:pattern=replacement)是对上述功能的简写。
#* 还有另一种简写形式，只替换后缀：$(text:suffix=replacement)。在这里，不使用%通配符。
#* 注意：在这种简写形式中，请不要添加额外的空格，否则会被视为搜索或替换的一部分。

# foo := a.o b.o l.a c.o
# one := $(patsubst %.o,%.c,$(foo))
# # This is a shorthand for the above
# two := $(foo:%.o=%.c)
# # This is the suffix-only shorthand, and is also equivalent to the above.
# three := $(foo:.o=.c)

# all:
# 	echo $(one)
# 	echo $(two)
# 	echo $(three)

#* 🟦 Foreach 函数
#* foreach函数的用法如下：$(foreach var,list,text)。
#* 它将一个由空格分隔的单词列表转换为另一个列表。
#* var变量会被依次设定为list中的每个单词，然后text将会对每个单词进行扩展。
#* 下面是一个示例，它在每个单词后面添加了感叹号：

# foo := who are you
# # For each "word" in foo, output that same word with an exclamation after
# bar := $(foreach wrd,$(foo),$(wrd)!)

# all:
# 	# Output is "who! are! you!"
# 	@echo $(bar)

#* 🟦 if函数
#* if函数用于检查第一个参数是否非空。
#* 如果是非空的，则执行第二个参数；否则执行第三个参数。

# foo := $(if this-is-not-empty,then!,else!)
# empty :=
# bar := $(if $(empty),then!,else!)

# all:
# 	@echo $(foo)
# 	@echo $(bar)

#* 🟦 call 函数
#* Make支持创建基本函数。你可以通过创建一个变量来"定义"函数，并使用参数$(0)、$(1)等。
#* 然后，你可以使用特殊的内置函数call来调用这个函数。语法为$(call 变量名, 参数1, 参数2)。
#* 其中$(0)代表变量名，而$(1)、$(2)等表示参数。

# sweet_new_fn = Variable Name: $(0) First: $(1) Second: $(2) Empty Variable: $(3)
# all: # Outputs "Variable Name: sweet_new_fn First: go Second: tigers Empty Variable:"
# 	@echo $(call sweet_new_fn, go, tigers)

#* 🟦 shell 函数
#* shell-这会调用shell，但会用空格替换换行符！
#TODO 这里有问题 显示 系统找不到指定的文件。
# Very ugly because the newlines are gone!
# all: 
# 	@echo $(shell dir) 