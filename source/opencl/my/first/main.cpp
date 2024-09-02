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

//* �ں˼���ÿ��Ԫ�� C = A + B
std::string kernel_code =
    "   void kernel simple_add(global const int* A, global const int* B, global int* C){ "
    "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 "
    "   }                                                                               ";

int main()
{
    //* ���û��OpenCLƽ̨ - ����ƽ̨���� 0��������˳���

    // OpenCL��һ���ؼ������������ֲ�ԡ���ˣ����磬���ܴ������
    // ����������£�CPU��GPU����������OpenCL���롣��ˣ�
    // һ�����õ�ʵ������֤OpenCLƽ̨����ѡ�����ĸ�����Ĵ��������С�
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if (all_platforms.size() == 0)
    {
        std::cout << " No OpenCL platforms found.\n";
        exit(1);
    }

    //* ���ǽ�ʹ�� id = = 0��ƽ̨
    cl::Platform default_platform = all_platforms[0];
    std::cout << "ƽ̨����: " << all_platforms.size() << std::endl;
    std::cout << "���е�ƽ̨: " << std::endl;
    // ��ӡ���е�ƽ̨
    for (const auto &platform : all_platforms)
    {
        std::cout << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
    }
    std::cout << "ʹ�õ�ƽ̨: " << default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    //* OpenCLƽ̨����ӵ�ж���豸���������Ĳ�����ȷ�����뽫�ڸ�ƽ̨�ĵ�һ���豸�����У�����ҵ��Ļ���
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0)
    {
        std::cout << " No devices found.\n";
        exit(1);
    }

    cl::Device default_device = all_devices[0];
    std::cout << "�豸����: " << all_devices.size() << std::endl;
    std::cout << "ʹ�õ��豸: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

    //* ����������
    cl::Context context({default_device});

    //* ���豸�ϴ���������
    cl::Buffer A_d(context, CL_MEM_READ_ONLY, sizeof(int) * SIZE);
    cl::Buffer B_d(context, CL_MEM_READ_ONLY, sizeof(int) * SIZE);
    cl::Buffer C_d(context, CL_MEM_WRITE_ONLY, sizeof(int) * SIZE);

    int A_h[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B_h[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    //* �������н��������͵��豸��
    cl::CommandQueue queue(context, default_device);

    //* ������ A �� B д���豸
    queue.enqueueWriteBuffer(A_d, CL_TRUE, 0, sizeof(int) * SIZE, A_h);
    queue.enqueueWriteBuffer(B_d, CL_TRUE, 0, sizeof(int) * SIZE, B_h);

    //* �������豸��ִ�еĴ�����󣬳�Ϊ�ںˣ�kernel��
    cl::Program::Sources sources;

    //* ���뵽�ںˣ��˴����ַ�����ʽ���֡�
    sources.push_back({kernel_code.c_str(), kernel_code.length()});

    //* OpenCL������ʱ�����ںˣ������Ϊʲô����ʾΪ�ַ�����ԭ��
    //* Ҳ�����߱����豸�˴���ķ�����
    cl::Program program(context, sources);
    if (program.build({default_device}) != CL_SUCCESS)
    {
        std::cout << " Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << "\n";
        exit(1);
    }
    //* �����������ʱ����������ǽ��ڳ���Ĵ˴����֡�

    //* �Ӱ�����simple_add���ں˵ĳ����У�����һ������ִ�е��ںˣ�
    //* ��������cl:buffer��Ϊ�������ݡ�
    //* ���������ͱ������ں˺����Ĳ���ƥ�䡣
    cl::compatibility::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer> simple_add(cl::Kernel(program, "simple_add"));
    
    //* ���ں���������Թ�ִ�е���ϸ��Ϣ��
    cl::NDRange global(SIZE);
    simple_add(cl::EnqueueArgs(queue, global), A_d, B_d, C_d).wait();

    int C_h[SIZE];
    //* ���豸������C_h��ȡ���C_d
    queue.enqueueReadBuffer(C_d, CL_TRUE, 0, sizeof(int) * SIZE, C_h);

    std::cout << " result: \n";
    for (int i = 0; i<10; i++) {
        std::cout << C_h[i] << " ";
    }

    return 0;
}
