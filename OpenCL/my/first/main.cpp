/*
 * @Author: linkenzone
 * @Date: 2023-09-18 11:17:43
 * @Descripttion: Do not edit
 */

#define SIZE 10
#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/opencl.hpp>

#include <iostream>

#define MAX_SOURCE_SIZE (0x100000)

//* 内核计算每个元素 C = A + B
std::string kernel_code =
    "   void kernel simple_add(global const int* A, global const int* B, global int* C){ "
    "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 "
    "   }                                                                               ";

int main()
{
    //* 如果没有OpenCL平台 - 所有平台等于 0，则程序将退出。

    // OpenCL的一个关键特性是其可移植性。因此，例如，可能存在情况
    // 在这种情况下，CPU和GPU都可以运行OpenCL代码。因此，
    // 一个良好的实践是验证OpenCL平台，以选择在哪个编译的代码上运行。
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if (all_platforms.size() == 0)
    {
        std::cout << " No OpenCL platforms found.\n";
        exit(1);
    }

    //* 我们将使用 id = = 0的平台
    cl::Platform default_platform = all_platforms[0];
    std::cout << "平台数量: " << all_platforms.size() << std::endl;
    std::cout << "所有的平台: " << std::endl;
    // 打印所有的平台
    for (const auto &platform : all_platforms)
    {
        std::cout << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
    }
    std::cout << "使用的平台: " << default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    //* OpenCL平台可能拥有多个设备。接下来的步骤是确保代码将在该平台的第一个设备上运行，如果找到的话。
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0)
    {
        std::cout << " No devices found.\n";
        exit(1);
    }

    cl::Device default_device = all_devices[0];
    std::cout << "设备数量: " << all_devices.size() << std::endl;
    std::cout << "使用的设备: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    //* 创建上下文
    cl::Context context({default_device});

    //* 在设备上创建缓冲区
    cl::Buffer A_d(context, CL_MEM_READ_ONLY, sizeof(int) * SIZE);
    cl::Buffer B_d(context, CL_MEM_READ_ONLY, sizeof(int) * SIZE);
    cl::Buffer C_d(context, CL_MEM_WRITE_ONLY, sizeof(int) * SIZE);

    int A_h[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B_h[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    //* 创建队列将命令推送到设备。
    cl::CommandQueue queue(context, default_device);

    //* 将数组 A 和 B 写入设备
    queue.enqueueWriteBuffer(A_d, CL_TRUE, 0, sizeof(int) * SIZE, A_h);
    queue.enqueueWriteBuffer(B_d, CL_TRUE, 0, sizeof(int) * SIZE, B_h);

    //* 定义在设备上执行的代码对象，称为内核（kernel）
    cl::Program::Sources sources;

    //* 加入到内核，此处以字符串形式呈现。
    sources.push_back({kernel_code.c_str(), kernel_code.length()});

    //* OpenCL在运行时编译内核，这就是为什么它表示为字符串的原因。
    //* 也有离线编译设备端代码的方法。
    cl::Program program(context, sources);
    if (program.build({default_device}) != CL_SUCCESS)
    {
        std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
        exit(1);
    }
    //* 如果发现运行时编译错误，它们将在程序的此处呈现。

    //* 从包含“simple_add”内核的程序中，创建一个用于执行的内核，
    //* 并将三个cl:buffer作为参数传递。
    //* 参数的类型必须与内核函数的参数匹配。
    cl::compatibility::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer> simple_add(cl::Kernel(program, "simple_add"));
    
    //* 将内核排入队列以供执行的详细信息。
    cl::NDRange global(SIZE);
    simple_add(cl::EnqueueArgs(queue, global), A_d, B_d, C_d).wait();

    int C_h[SIZE];
    //* 从设备向数组C_h读取结果C_d
    queue.enqueueReadBuffer(C_d, CL_TRUE, 0, sizeof(int) * SIZE, C_h);

    std::cout << " result: \n";
    for (int i = 0; i<10; i++) {
        std::cout << C_h[i] << " ";
    }

    return 0;
}
