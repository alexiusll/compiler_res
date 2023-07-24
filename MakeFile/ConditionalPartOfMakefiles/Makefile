#* 🟦 if/false 情况

# foo = ok

# all:
# ifeq ($(foo), ok)
# 	echo "foo equals ok"
# else
# 	echo "nope"
# endif

#* 🟦 检查一个变量是否为空

# nullstring =
# foo = $(nullstring) # end of line; there is a space here

# all:
# ifeq ($(strip $(foo)),)
# 	echo "foo is empty after being stripped"
# endif
# ifeq ($(nullstring),)
# 	echo "nullstring doesn't even have spaces"
# endif

#* 🟦 检查一个变量是否被定义

# ifdef does not expand variable references; it just sees if something is defined at all

# bar =
# foo = $(bar)

# all:
# ifdef foo
# 	echo "foo is defined"
# endif
# ifndef bar
# 	echo "but bar is not"
# endif

#* $(MAKEFLAGS)
#* This example shows you how to test make flags with findstring and MAKEFLAGS. 
#* Run this example with make -i to see it print out the echo statement.

all:
# Search for the "-i" flag. MAKEFLAGS is just a list of single characters, one per flag. So look for "i" in this case.
ifneq (,$(findstring i, $(MAKEFLAGS)))
	echo "i was passed to MAKEFLAGS"
endif