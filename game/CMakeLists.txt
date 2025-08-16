# 要求的最低CMake版本
cmake_minimum_required(VERSION 3.10.0)

# 指定项目名称、版本和使用的语言
project(SpaceShooter VERSION 0.1.0 LANGUAGES C CXX)

# 添加本项目下的 SDL2 路径
set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdlibs/SDL2")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL2_LIBRARY "${SDL2_DIR}/lib/x64/SDL2.lib")
set(SDL2MAIN_LIBRARY "${SDL2_DIR}/lib/x64/SDL2main.lib")

# 设置编译选项
if(MSVC)
    add_compile_options("/source-charset:utf-8")
endif()

# 包含 SDL2 头文件
include_directories(${SDL2_INCLUDE_DIR})
# 添加其他CPP源文件
#aux_source_directory(./game GAME_SRCS)
# 构建可执行文件的名称和源代码文件（需编译的源文件）
add_executable(SpaceShooter main.cpp)

# 链接 SDL2 静态库
target_link_libraries(SpaceShooter ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})