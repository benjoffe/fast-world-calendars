cmake_minimum_required(VERSION 3.14)
project(fast-world-calendars VERSION 1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 26)

if(NOT MSVC)
  add_compile_options(-Wall -Wextra -O3 -march=native)
endif()

option(SANITIZE "Enable -fsanitize=signed-integer-overflow" OFF)
if(SANITIZE)
  add_compile_options(-fsanitize=signed-integer-overflow)
  add_link_options(-fsanitize=signed-integer-overflow)
endif()

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

#---------------------------------------------------------------------------
# Google Benchmark
#---------------------------------------------------------------------------

include(FetchContent)

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.9.1
  SOURCE_DIR     ${CMAKE_SOURCE_DIR}/tp/benchmark
)
set(BENCHMARK_ENABLE_TESTING OFF)
# Pi Zero and other constrained targets can't run CMake probe executables during
# configure; pre-set the regex backend so benchmark skips its try_run checks.
if(NOT HAVE_POSIX_REGEX AND NOT HAVE_STD_REGEX AND NOT HAVE_GNU_POSIX_REGEX)
  set(HAVE_POSIX_REGEX 1 CACHE INTERNAL "")
endif()
FetchContent_MakeAvailable(benchmark)

#---------------------------------------------------------------------------
# Weekday
#---------------------------------------------------------------------------

add_executable(weekday_test weekday/weekday_test.cpp)
add_executable(weekday_bench weekday/weekday_bench.cpp)
target_link_libraries(weekday_bench benchmark::benchmark)
if(APPLE)
  target_link_options(weekday_bench PRIVATE -Wl,-no_deduplicate)
  target_compile_options(weekday_bench PRIVATE -mno-outline)
endif()
