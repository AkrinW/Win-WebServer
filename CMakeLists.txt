# a cmake list file
cmake_minimum_required(VERSION 3.5)
# project name
# set(CMAKE_C_COMPILER "C:/Files/w64devkit/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/mingw/bin/g++.exe")
project(Webserver)

# 定义变量
SET(MAIN main.cpp)
SET(CLIENT client.cpp)
SET(SERVER server.cpp)


# 指定cpp版本
SET(CMAKE_CXX_STANDARD 17)
# 指定存储路径
SET(Home "D:/study/Win-WebServer")
SET(EXECUTABLE_OUTPUT_PATH ${Home})
# 包含头文件
include_directories("${PROJECT_SOURCE_DIR}/include")

# 搜索路径另一种方式
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main ${MAIN} ${SRC_LIST})
add_executable(server ${SERVER})
add_executable(client ${CLIENT})
# 链接库
target_link_libraries(main ws2_32)
target_link_libraries(server ws2_32)
target_link_libraries(client ws2_32)

# cmake_minimum_required(VERSION 3.5)

# # Project name
# project(Webserver)

# # Specify the C++ compiler
# set(CMAKE_CXX_COMPILER "C:/Files/mingw/bin/g++.exe")

# # Specify C++ standard
# set(CMAKE_CXX_STANDARD 17)

# # Specify output path
# set(Home "D:/study/Win-WebServer")
# set(EXECUTABLE_OUTPUT_PATH ${Home})

# # Include directories
# include_directories("${PROJECT_SOURCE_DIR}/include")

# # Search for source files
# set(SRC_LIST main.cpp)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# # Define the executable
# add_executable(Webserver ${SRC_LIST})

# # Link libraries
# target_link_libraries(Webserver ws2_32)