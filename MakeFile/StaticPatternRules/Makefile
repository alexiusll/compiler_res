CC = gcc

objects = foo.o bar.o all.o
allin.exe: $(objects)

# These files compile via implicit rules
# foo.o: foo.c
# bar.o: bar.c
# all.o: all.c

# 这些文件通过隐含规则进行编译。
# 语法 - 目标 ...：目标模式：先决条件模式...
# 对于第一个目标，foo.o，目标模式匹配foo.o并将“词根”设置为“foo”。
# 然后，它用该词根替换先决条件模式中的“%”。
$(objects): %.o: %.c

all.c:
	echo int main() { return 0; } > all.c

%.c:
	echo. > $@
	
clean:
	rm -f *.c *.o all