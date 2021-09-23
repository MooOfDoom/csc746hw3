cmake_minimum_required(VERSION 3.14)
project(hw2 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE "Release")

find_package(BLAS REQUIRED)

# We require the GNU compiler for this assignment.
if (NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(Prg-Intel "PrgEnv-intel")
    set(Prg-Clang "PrgEnv-cray")
    message(WARNING
            "Must use GNU Compiler for submission. Make sure you ran:\n"
            "module swap ${Prg-${CMAKE_C_COMPILER_ID}} PrgEnv-gnu")
endif ()

# Common library target for benchmarking.
add_library(benchmark OBJECT benchmark.cpp)
target_compile_features(benchmark PRIVATE cxx_std_11)

add_executable(benchmark-basic dgemv-basic.cpp)
target_link_libraries(benchmark-basic PRIVATE benchmark ${BLAS_LIBRARIES})
target_compile_features(benchmark-basic PRIVATE c_std_11 c_restrict)
target_compile_options(benchmark-basic PRIVATE -Wall -pedantic -march=native)
set(BENCHMARK "basic")
configure_file(job.in job-${BENCHMARK})

add_executable(benchmark-blas dgemv-blas.cpp)
target_link_libraries(benchmark-blas PRIVATE benchmark ${BLAS_LIBRARIES})
target_compile_features(benchmark-blas PRIVATE c_std_11 c_restrict)
target_compile_options(benchmark-blas PRIVATE -Wall -pedantic -march=native)
set(BENCHMARK "blas")
configure_file(job.in job-${BENCHMARK})

add_executable(benchmark-openmp dgemv-openmp.cpp)
target_link_libraries(benchmark-openmp PRIVATE benchmark ${BLAS_LIBRARIES})
target_link_options(benchmark-openmp PRIVATE -fopenmp)
target_compile_features(benchmark-openmp PRIVATE c_std_11 c_restrict)
target_compile_options(benchmark-openmp PRIVATE -fopenmp -Wall -pedantic -march=native)
set(BENCHMARK "openmp")
configure_file(job.in job-${BENCHMARK})

add_executable(benchmark-openmp-exp dgemv-openmp.cpp)
target_compile_definitions(benchmark-openmp-exp PRIVATE EXPLICIT=1)
target_link_libraries(benchmark-openmp-exp PRIVATE benchmark ${BLAS_LIBRARIES})
target_link_options(benchmark-openmp-exp PRIVATE -fopenmp)
target_compile_features(benchmark-openmp-exp PRIVATE c_std_11 c_restrict)
target_compile_options(benchmark-openmp-exp PRIVATE -fopenmp -Wall -pedantic -march=native)
set(BENCHMARK "openmp-exp")
configure_file(job.in job-${BENCHMARK})

add_executable(benchmark-openmp-nest dgemv-openmp.cpp)
target_compile_definitions(benchmark-openmp-nest PRIVATE NESTED=1)
target_link_libraries(benchmark-openmp-nest PRIVATE benchmark ${BLAS_LIBRARIES})
target_link_options(benchmark-openmp-nest PRIVATE -fopenmp)
target_compile_features(benchmark-openmp-nest PRIVATE c_std_11 c_restrict)
target_compile_options(benchmark-openmp-nest PRIVATE -fopenmp -Wall -pedantic -march=native)
set(BENCHMARK "openmp-nest")
configure_file(job.in job-${BENCHMARK})

add_executable(benchmark-openmp-coll dgemv-openmp.cpp)
target_compile_definitions(benchmark-openmp-coll PRIVATE COLLAPSE=1)
target_link_libraries(benchmark-openmp-coll PRIVATE benchmark ${BLAS_LIBRARIES})
target_link_options(benchmark-openmp-coll PRIVATE -fopenmp)
target_compile_features(benchmark-openmp-coll PRIVATE c_std_11 c_restrict)
target_compile_options(benchmark-openmp-coll PRIVATE -fopenmp -Wall -pedantic -march=native)
set(BENCHMARK "openmp-coll")
configure_file(job.in job-${BENCHMARK})

