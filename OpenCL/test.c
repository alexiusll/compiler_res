/*
 * @Author: linkenzone
 * @Date: 2023-07-21 10:05:20
 * @Descripttion: Do not edit
 */
// C standard includes
#include <stdio.h>

// OpenCL includes
#include <CL/cl.h>

// test rebase

int main()
{
    cl_int CL_err = CL_SUCCESS;
    cl_uint numPlatforms = 0;

    CL_err = clGetPlatformIDs( 0, NULL, &numPlatforms );

    if (CL_err == CL_SUCCESS)
        printf_s("%u platform(s) found\n", numPlatforms);
    else
        printf_s("clGetPlatformIDs(%i)\n", CL_err);

    return 0;
}