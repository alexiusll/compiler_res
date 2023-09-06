chcp 65001

::  Clang 9（及更高版本）可以编译使用OpenCL C语言编写的OpenCL内核。
::  您可以通过传递 -emit-llvm 标志来告诉Clang生成LLVM-IR（将 -S 添加到输出文本中，而不是字节码格式），
::  并且可以使用 -cl-std=CL2.0 等选项来指定使用哪个版本的OpenCL标准。Clang目前支持OpenCL 2.0。
::  -c：这是一个编译选项，表示只进行编译而不进行链接。编译后的结果将是目标文件（.o文件或LLVM IR）
::  -x cl：这是一个指定输入文件类型的选项。-x cl 表示输入文件是OpenCL源代码。
::  -emit-llvm：这个选项告诉编译器生成LLVM IR。这意味着编译器将OpenCL源代码转换为LLVM中间表示。
::  -S：这是一个输出选项，表示输出LLVM IR的文本表示（汇编）。如果省略此选项，将生成二进制格式的LLVM IR。
::  -cl-std=CL2.0：这是一个OpenCL选项，指定使用的OpenCL标准版本。在这里，它指定使用OpenCL 2.0标准。

:: clang -c -o0 -x cl -target spir -emit-llvm -cl-std=CL1.2 -fdiscard-value-names -Xclang ^
:: -finclude-default-header vector_add_kernel.cl -o vector_add_kernel.bc

clang -c -x cl -target spir -emit-llvm -cl-std=CL1.2 vector_add_kernel.cl -o vector_add_kernel.bc