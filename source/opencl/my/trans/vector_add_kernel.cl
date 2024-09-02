__kernel void vector_add(__global int *input, __global int *output) {

  // Get the index of the current element
  int gid = get_global_id(0);

  // Do the operation
  // C[i] = A[i] + B[i];

  // float2 test;

  // 声明一个 float4 向量
  int3 myVector = (int3)(1, 0, 1);

  if(any(myVector)){
    // 将结果写入输出数组
    output[gid] = 0;
  } else {
    output[gid] = 1;
  }

  // 使用any函数检查向量中是否有任何一个分量大于阈值
  // bool isAnyGreater = all(myVector);
}
