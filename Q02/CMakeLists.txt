# cmake最低版本
cmake_minimum_required(VERSION 3.8)
# 命名项目
project(JosephProblem VERSION 1.0.3)
# 添加源文件
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp")
# 添加头文件
include_directories(./include)
include_directories(../templates)
# 添加生成可执行文件
add_executable(Question02-JosephProblem ${SRC_DIR_LIST})
# 设置版本号
set_target_properties(Question02-JosephProblem PROPERTIES VERSION v1.0.3)

