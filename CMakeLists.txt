cmake_minimum_required(VERSION 3.10.0)
project(SpaceShooter)

set(CMAKE_CXX_STANDARD 20)

# 添加源文件
aux_source_directory(./game GAME_SRCS)

# 需编译的源文件
add_executable(SpaceShooter ${GAME_SRCS})