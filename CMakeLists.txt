cmake_minimum_required(VERSION 3.20)
project(lab_git_tests)
set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

# заголовки
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- зібрати всі .cpp із src/ ----
file(GLOB SRCS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# якщо є main.cpp — робимо окремий таргет застосунку
if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    # Вилучаємо main.cpp зі списку SRCS, щоб не дублювався
    list(REMOVE_ITEM SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_executable(shop_app src/main.cpp ${SRCS})
endif()

# ---- GoogleTest тільки для тестів ----
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- тести ----
enable_testing()
file(GLOB TESTS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

add_executable(shop_tests ${TESTS} ${SRCS})
target_link_libraries(shop_tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(shop_tests)

# (опційно) попередження
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()
