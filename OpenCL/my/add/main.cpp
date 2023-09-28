/*
 * @Author: linkenzone
 * @Date: 2023-07-28 11:53:00
 * @Descripttion:
 *
 * https://www.eriksmistad.no/getting-started-with-opencl-and-gpu-computing/
 */

#include <stdio.h>
#include <stdlib.h>

#define CL_HPP_TARGET_OPENCL_VERSION 200
#include <CL/opencl.hpp>

#define MAX_SOURCE_SIZE (0x100000)

class test
{
public:
  int a;
  char b;
};

int main(void)
{
  //* 生成随机数作为输入
  int i;
  const int LIST_SIZE = 1024;
  int *A = (int *)malloc(sizeof(int) * LIST_SIZE);
  int *B = (int *)malloc(sizeof(int) * LIST_SIZE);
  for (i = 0; i < LIST_SIZE; i++)
  {
    A[i] = i;
    B[i] = LIST_SIZE - i;
  }

  test *_test = new test();
  _test->a = 111;
  _test->b = 'c';

  //* 将内核源代码加载到数组 source_str 中
  FILE *fp;
  char *source_str;
  size_t source_size;

  fp = fopen("vector_add_kernel.cl", "r");
  if (!fp)
  {
    fprintf(stderr, "Failed to load kernel.\n");
    exit(1);
  }
  source_str = (char *)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);

  //* 获取平台和设备信息
  cl_platform_id platform_id = NULL;
  cl_device_id device_id = NULL;
  cl_uint ret_num_devices;
  cl_uint ret_num_platforms;
  cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 1, &device_id,
                       &ret_num_devices);

  //* 创建OpenCL 上下文
  cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

  //* 创建命令队列，注意需要以 上下文 和 设备id 作为参数
  cl_command_queue command_queue =
      clCreateCommandQueue(context, device_id, 0, &ret);

  //* 在设备上为每个vector创建内存缓冲区
  cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                    LIST_SIZE * sizeof(int), NULL, &ret);
  cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
                                    LIST_SIZE * sizeof(int), NULL, &ret);
  cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                    LIST_SIZE * sizeof(int), NULL, &ret);

  //* 将列表 A 和 B 复制到各自的内存缓冲区中
  ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,
                             LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
  ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,
                             LIST_SIZE * sizeof(int), B, 0, NULL, NULL);

  //* 从内核源代码创建程序
  cl_program program =
      clCreateProgramWithSource(context, 1, (const char **)&source_str,
                                (const size_t *)&source_size, &ret);

  //* 编译程序
  ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

  //* 创建 OpenCL kernel
  cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

  //* 设置 kernel 参数
  ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
  ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
  ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);

  //* 执行列表中的 OpenCL kernel
  size_t global_item_size = LIST_SIZE; // 处理整个列表
  size_t local_item_size = 64;         // 按 64 一组进行处理
  ret =
      clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size,
                             &local_item_size, 0, NULL, NULL);

  //* 将设备上的内存缓冲区 C 读入本地变量 C
  int *C = (int *)malloc(sizeof(int) * LIST_SIZE);
  ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,
                            LIST_SIZE * sizeof(int), C, 0, NULL, NULL);

  // Display the result to the screen
  for (i = 0; i < LIST_SIZE; i++)
    printf("%d + %d = %d\n", A[i], B[i], C[i]);

  // Clean up
  ret = clFlush(command_queue);
  ret = clFinish(command_queue);
  ret = clReleaseKernel(kernel);
  ret = clReleaseProgram(program);
  ret = clReleaseMemObject(a_mem_obj);
  ret = clReleaseMemObject(b_mem_obj);
  ret = clReleaseMemObject(c_mem_obj);
  ret = clReleaseCommandQueue(command_queue);
  ret = clReleaseContext(context);
  free(A);
  free(B);
  free(C);
  return 0;
}