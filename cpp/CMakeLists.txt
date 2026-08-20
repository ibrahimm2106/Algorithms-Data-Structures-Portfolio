cmake_minimum_required(VERSION 3.16)
project(OnlineStoreAlgorithms LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(online_store src/OnlineStore.cpp)
target_include_directories(online_store PUBLIC include)

if(MSVC)
    target_compile_options(online_store PRIVATE /W4)
else()
    target_compile_options(online_store PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(online_store_demo src/main.cpp)
target_link_libraries(online_store_demo PRIVATE online_store)

include(CTest)
if(BUILD_TESTING)
    add_executable(online_store_tests tests/test_online_store.cpp)
    target_link_libraries(online_store_tests PRIVATE online_store)
    add_test(NAME online_store_tests COMMAND online_store_tests)
endif()
