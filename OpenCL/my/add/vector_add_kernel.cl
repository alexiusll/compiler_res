__kernel void vector_add(__global int *A, __global int *B, __global int *C) {

  // Get the index of the current element
  int gid = get_global_id(0);

  // Do the operation
  C[gid] = A[gid] + B[gid];
}
