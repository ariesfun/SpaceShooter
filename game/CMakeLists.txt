# 要求的最低CMake版本
cmake_minimum_required(VERSION 3.10.0)

# 指定项目名称、版本和使用的语言
project(SpaceShooter VERSION 0.1.0 LANGUAGES C CXX)

# 设置编译器CPP标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加本项目下的 SDL2 路径
set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdlibs/SDL2")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL2_LIBRARY "${SDL2_DIR}/lib/x64/SDL2.lib")
set(SDL2MAIN_LIBRARY "${SDL2_DIR}/lib/x64/SDL2main.lib")
set(SDL2_IMAGE_LIBRARY "${SDL2_DIR}/lib/x64/SDL2_image.lib")
set(SDL2_MIXER_LIBRARY "${SDL2_DIR}/lib/x64/SDL2_mixer.lib")
set(SDL2_TTF_LIBRARY "${SDL2_DIR}/lib/x64/SDL2_ttf.lib")

# 设置编译选项
if(MSVC)
    add_compile_options("/source-charset:utf-8")
    add_compile_options(/W4) # 开启编译器警告
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 指定可执行文件的生成输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})
# 同时根据平台名称指定生成的程序名称, 如Win平台："SpaceShooter-Windows.exe "
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 设置当前项目包含的头文件目录
set(CURRENT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
# 包含 SDL2 头文件
include_directories(${SDL2_INCLUDE_DIR} ${CURRENT_INCLUDE_DIR})
# 添加其他CPP源文件
aux_source_directory(src/ GAME_SRCS)
# 构建可执行文件的名称和源代码文件（需编译的源文件）
add_executable(${TARGET} main.cpp ${GAME_SRCS})

# 链接 SDL2 静态库
target_link_libraries(${TARGET} 
                     ${SDL2_LIBRARY} 
                     ${SDL2MAIN_LIBRARY} 
                     ${SDL2_IMAGE_LIBRARY}
                     ${SDL2_MIXER_LIBRARY}
                     ${SDL2_TTF_LIBRARY})