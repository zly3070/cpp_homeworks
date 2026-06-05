cmake_minimum_required(VERSION 3.11)
project(AlumniSystem)

# 设置 C++ 标准为 C++17，你的代码里用到了很多现代特性
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 FTXUI 库
find_package(ftxui REQUIRED COMPONENTS screen dom component)

# 添加可执行文件，把 main.cpp 和 Alumni.h 里实现的 cpp 文件都加上
# 如果你有单独的 Alumni.cpp 文件，也要加在后面
add_executable(try try.cpp)

# 把 FTXUI 的库链接到你的可执行文件
target_link_libraries(try
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)