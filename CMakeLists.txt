cmake_minimum_required(VERSION 2.8.11)
project(hpmpc)

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

# build variables
set(BLASFEO_PATH ${PROJECT_SOURCE_DIR}/../blasfeo)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -fPIC -lm -DTARGET_C99_4X4 -DBLASFEO -I${BLASFEO_PATH}/include")

# add library
add_library(hpmpc SHARED ${HPMPC_SRC})
target_link_libraries(hpmpc m)
