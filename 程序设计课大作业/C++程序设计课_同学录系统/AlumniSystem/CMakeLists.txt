cmake_minimum_required(VERSION 3.11)
project(AlumniSystem)

# Cpp17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 FTXUI 库
find_package(ftxui REQUIRED COMPONENTS screen dom component)

# 添加可执行文件，把 main.cpp 和 Alumni.h 里实现的 cpp 文件都加上
add_executable(try try.cpp)

# 链接FTXUI库到可执行文件
target_link_libraries(try
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)