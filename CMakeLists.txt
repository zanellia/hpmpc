cmake_minimum_required(VERSION 2.8.11)
project(hpmpc)

# target architecture. currently supported (more architectures are available with the older v0.1 release):
# X64_AVX2   : machine with AVX2 and FMA3 instruction sets (recent Intel and AMD processors), 64 bit operating system, code optimized for Intel Haswell.
# X64_AVX    : machine with AVX instruction set (previous generation Intel and AMD processors), 64 bit operating system, code optimized for Intel Sandy-Bridge.
# X64_SSE3   : machine with SSE3 instruction set (older Intel and AMD processors), 64 bit operating system, code optimized for Intel Core.
# CORTEX_A57 : machine with ARMv8a processor with NEON, 64-bit operating system, code optimized for ARM Cortex A57.
# CORTEX_A15 : machine with ARMv7a processor with VPFv3 (D32 versions) and NEON, code optimized for ARM Cortex A15.
# CORTEX_A9  : machine with ARMv7a processor with VPFv3 (D32 versions) and NEON, code optimized for ARM Cortex A9.
# CORTEX_A7  : machine with ARMv7a processor with VPFv3 (D32 versions) and NEON, code optimized for ARM Cortex A7.
# C99_4X4    : c99 reference code, performing better on a machine with at least 32 scalar registers.
set(TARGET X64_AVX)

# use BLASFEO?
set(USE_BLASFEO 1)
set(BLASFEO_PATH ${PROJECT_SOURCE_DIR}/../blasfeo)

# C Compiler
# set(CC_COMPILER gcc)
# set(MINGW_ROOT ~/cross_compiler_windows)  (can be obtained here: https://sourceforge.net/projects/mingw-w64/files/)
# set(CC_COMPILER ${MINGW_ROOT}/mingw-w64-bin_x86_64-linux_20131228/bin/x86_64-w64-mingw32-gcc)
# set(CC_COMPILER /opt/gcc/bin/gcc) # custom gcc
# set(CC_COMPILER clang)

# operative system
set(OS LINUX)
# set(OS WINDOWS)

# installation directory
set(PREFIX /usr)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fPIC -lm -DTARGET_C99_4X4 -DBLASFEO -I${BLASFEO_PATH}/include")

# common optimization/debugging flags
set(COMMON_FLAGS "-g -fPIC")
if(${USE_BLASFEO} EQUAL 1)
	set(COMMON_FLAGS "${COMMON_FLAGS} -DBLASFEO -I${BLASFEO_PATH}/include")
endif(${USE_BLASFEO} EQUAL 1)

if(${OS} EQUAL WINDOWS)
	set(COMMON_FLAGS "${COMMON_FLAGS} -DOS_WINDOWS")
endif(${OS} EQUAL WINDOWS)

set(DEBUG "-pedantic -Wfloat-equal")
# set(LDFLAGS "")

# reference code linking to standard BLAS and LAPACK
# 0
# OPENBLAS
# BLIS
# NETLIB
# MKL

# reference implementation
set(REF_BLAS 0)
if(${REF_BLAS} EQUAL 0)
	set(REF_BLAS_FLAGS "")
endif(${REF_BLAS} EQUAL 0)

if(${REF_BLAS} EQUAL OPENBLAS)
	set(REF_BLAS_FLAGS -DREF_BLAS_OPENBLAS)
endif(${REF_BLAS} EQUAL OPENBLAS)

if(${REF_BLAS} EQUAL BLIS)
	set(REF_BLAS_FLAGS -DREF_BLAS_BLIS)
endif(${REF_BLAS} EQUAL BLIS)

if(${REF_BLAS} EQUAL NETLIB)
	set(REF_BLAS_FLAGS -DREF_BLAS_NETLIB)
endif(${REF_BLAS} EQUAL NETLIB)

if(${REF_BLAS} EQUAL MKL)
	set(REF_BLAS_FLAGS -DREF_BLAS_MKL)
	set(COMMON_FLAGS "${COMMON_FLAGS} -m64 -I/opt/intel/mkl/include")
endif(${REF_BLAS} EQUAL MKL)

# architecture-specific optimization flags
if(${TARGET} EQUAL X64_AVX2)
	set(CFLAGS "$(COMMON_FLAGS) -m64 -mavx2 -mfma -DTARGET_X64_AVX2 $(REF_BLAS_FLAGS) $(DEBUG}")
endif(${TARGET} EQUAL X64_AVX2)

if(${TARGET} EQUAL X64_AVX)
	set(CFLAGS "${COMMON_FLAGS} -m64 -mavx -DTARGET_X64_AVX ${REF_BLAS_FLAGS} ${DEBUG}")
endif(${TARGET} EQUAL X64_AVX)

if(${TARGET} EQUAL X64_SSE3)
	set(CFLAGS "${COMMON_FLAGS} -m64 -msse3 -DTARGET_X64_SSE3 ${REF_BLAS_FLAGS} ${DEBUG}")
endif(${TARGET} EQUAL X64_SSE3)

if(${TARGET} EQUAL C99_4X4)
	set(CFLAGS "${COMMON_FLAGS} -DTARGET_C99_4X4 ${REF_BLAS_FLAGS} ${DEBUG}")
endif(${TARGET} EQUAL C99_4X4)

if(${TARGET} EQUAL C99_4X4_PREFETCH)
	set(CFLAGS "${COMMON_FLAGS} -march=native -DTARGET_C99_4X4_PREFETCH ${REF_BLAS_FLAGS} $(DEBUG)")
endif(${TARGET} EQUAL C99_4X4_PREFETCH)

if(${TARGET} EQUAL CORTEX_A57)
	set(CFLAGS "${COMMON_FLAGS} -march=armv8-a+fp+simd -mcpu=cortex-a57 -DTARGET_CORTEX_A57 ${REF_BLAS_FLAGS} ${DEBUG}")
endif(${TARGET} EQUAL CORTEX_A57)

if(${TARGET} EQUAL CORTEX_A15)
	set(CFLAGS "${COMMON_FLAGS} -marm -mfloat-abi=hard -mfpu=neon-vfpv4 -mcpu=cortex-a15 -DTARGET_CORTEX_A15 ${REF_BLAS_FLAGS} $(DEBUG)")
endif(${TARGET} EQUAL CORTEX_A15)

if(${TARGET} EQUAL CORTEX_A9)
	set(CFLAGS "${COMMON_FLAGS} -marm -mfloat-abi=hard -mfpu=neon -mcpu=cortex-a9 -DTARGET_CORTEX_A9 ${REF_BLAS_FLAGS} ${DEBUG}")
endif(${TARGET} EQUAL CORTEX_A9)

if(${TARGET} EQUAL CORTEX_A7)
	set(CFLAGS "${COMMON_FLAGS} -marm -mfloat-abi=hard -mfpu=neon-vfpv4 -mcpu=cortex-a7 -DTARGET_CORTEX_A7 ${REF_BLAS_FLAGS} ${DEBUG}")
endif(${TARGET} EQUAL CORTEX_A7)

# source files
file(GLOB HPMPC_AUXILIARY_SRC
	${PROJECT_SOURCE_DIR}/auxiliary/d_aux_lib4.c
	${PROJECT_SOURCE_DIR}/auxiliary/d_aux_extern_depend_lib4.c
	${PROJECT_SOURCE_DIR}/auxiliary/i_aux.c)

file(GLOB HPMPC_LCQP_SOLVERS_SRC ${PROJECT_SOURCE_DIR}/lqcp_solvers/d_back_ric_rec_libstr.c
	${PROJECT_SOURCE_DIR}/lqcp_solvers/d_part_cond_libstr.c)

file(GLOB HPMPC_MPC_AUXILIARY_SRC
	${PROJECT_SOURCE_DIR}/mpc_solvers/c99/d_aux_ip_hard_libstr.c
	${PROJECT_SOURCE_DIR}/mpc_solvers/c99/d_res_ip_res_hard_libstr.c)

file(GLOB HPMPC_MPC_SOLVERS_SRC
	${PROJECT_SOURCE_DIR}/mpc_solvers/d_ip2_res_hard_libstr.c)

file(GLOB HPMPC_MPC_INTERFACES_SRC ${PROJECT_SOURCE_DIR}/interfaces/c/fortran_order_interface_libstr.c)

set(HPMPC_SRC ${HPMPC_AUXILIARY_SRC} ${HPMPC_KERNEL_SRC} ${HPMPC_BLAS_SRC} ${HPMPC_LCQP_SOLVERS_SRC}
	${HPMPC_MPC_AUXILIARY_SRC} ${HPMPC_MPC_SOLVERS_SRC} ${HPMPC_MPC_SOLVERS_C99_SRC} ${HPMPC_MPC_INTERFACES_SRC})


# add library
add_library(hpmpc SHARED ${HPMPC_SRC})
target_link_libraries(hpmpc m)
