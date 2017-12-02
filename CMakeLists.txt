cmake_minimum_required(VERSION 3.9)
project(Boost-Learning)

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )

# 添加cmake_modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# 添加库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 添加可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


set(Boost_USE_MULTITHREADED ON) #开启boost多线程支持
###################dependencies#######################
find_package(Boost COMPONENTS system filesystem thread)


message(Boost_version: ${Boost_VERSION})
message(Boost_Lib: ${Boost_LIBRARIES})

# 添加头文件
include_directories(
        ${BOOST_INCLUDE_DIR}
)

# 添加依赖库
set(THIRD_PARTY_LIBS
        ${Boost_LIBRARIES}
        )

#######################SubCmakeList#############################
add_subdirectory(src)
