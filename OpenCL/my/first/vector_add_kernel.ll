; ModuleID = 'vector_add_kernel.cl'
source_filename = "vector_add_kernel.cl"
target datalayout = "e-p:32:32-i64:64-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "spir"

; Function Attrs: convergent mustprogress nofree norecurse nounwind willreturn memory(argmem: readwrite)
define dso_local spir_kernel void @vector_add(ptr addrspace(1) nocapture noundef readonly align 4 %0, ptr addrspace(1) nocapture noundef readonly align 4 %1, ptr addrspace(1) nocapture noundef writeonly align 4 %2) local_unnamed_addr #0 !kernel_arg_addr_space !4 !kernel_arg_access_qual !5 !kernel_arg_type !6 !kernel_arg_base_type !6 !kernel_arg_type_qual !7 {
  %4 = tail call spir_func i32 @_Z13get_global_idj(i32 noundef 0) #2
  %5 = getelementptr inbounds i32, ptr addrspace(1) %0, i32 %4
  %6 = load i32, ptr addrspace(1) %5, align 4, !tbaa !8
  %7 = getelementptr inbounds i32, ptr addrspace(1) %1, i32 %4
  %8 = load i32, ptr addrspace(1) %7, align 4, !tbaa !8
  %9 = add nsw i32 %8, %6
  %10 = getelementptr inbounds i32, ptr addrspace(1) %2, i32 %4
  store i32 %9, ptr addrspace(1) %10, align 4, !tbaa !8
  ret void
}

; Function Attrs: convergent mustprogress nofree nounwind willreturn memory(none)
declare dso_local spir_func i32 @_Z13get_global_idj(i32 noundef) local_unnamed_addr #1

attributes #0 = { convergent mustprogress nofree norecurse nounwind willreturn memory(argmem: readwrite) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "uniform-work-group-size"="true" }
attributes #1 = { convergent mustprogress nofree nounwind willreturn memory(none) "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" }
attributes #2 = { convergent nounwind willreturn memory(none) }

!llvm.module.flags = !{!0, !1}
!opencl.ocl.version = !{!2}
!opencl.spir.version = !{!2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"frame-pointer", i32 2}
!2 = !{i32 1, i32 2}
!3 = !{!"clang version 16.0.0"}
!4 = !{i32 1, i32 1, i32 1}
!5 = !{!"none", !"none", !"none"}
!6 = !{!"int*", !"int*", !"int*"}
!7 = !{!"", !"", !""}
!8 = !{!9, !9, i64 0}
!9 = !{!"int", !10, i64 0}
!10 = !{!"omnipotent char", !11, i64 0}
!11 = !{!"Simple C/C++ TBAA"}
