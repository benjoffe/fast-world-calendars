cmake_minimum_required(VERSION 3.14)
project(fast-world-calendars VERSION 1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

if(NOT MSVC)
  add_compile_options(-Wall -Wextra -O3)
  if(NOT CMAKE_CROSSCOMPILING)
    add_compile_options(-march=native)
  endif()
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

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # GCC doesn't treat _Static_assert as a keyword in C++ mode, but macOS SDK
  # headers (mach/message.h) use it. Map it to the C++ equivalent.
  target_compile_options(benchmark PRIVATE -D_Static_assert=static_assert)
endif()

#---------------------------------------------------------------------------
# Weekday
#---------------------------------------------------------------------------

add_executable(weekday_test weekday/weekday_test.cpp)
add_executable(weekday_bench weekday/weekday_bench.cpp)
target_link_libraries(weekday_bench benchmark::benchmark)
if(APPLE)
  target_link_options(weekday_bench PRIVATE -Wl,-no_deduplicate)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(weekday_bench PRIVATE -mno-outline)
  endif()
endif()

#---------------------------------------------------------------------------
# Time of Day
#---------------------------------------------------------------------------

add_executable(time_test time/time_test.cpp)
add_executable(time_bench time/time_bench.cpp)
target_link_libraries(time_bench benchmark::benchmark)
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # time_bench.cpp asks the vectorizer to at least try on every -vector loop
  # (some algorithms genuinely can't vectorize, e.g. real 64-bit division) --
  # that's expected and not worth a warning on every build.
  target_compile_options(time_bench PRIVATE -Wno-pass-failed)
endif()
if(APPLE)
  target_link_options(time_bench PRIVATE -Wl,-no_deduplicate)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(time_bench PRIVATE -mno-outline)
  endif()
endif()
