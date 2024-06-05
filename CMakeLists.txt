
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(udpsocket)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加源文件
add_executable(udpsocket main.cpp UdpSocket.cpp)
