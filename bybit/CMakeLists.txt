PROJECT(bybit)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# 导入全部文件
#AUX_SOURCE_DIRECTORY(. DIR_SRCS)


# 直接是全路径
#link_libraries(“/home/server/third/lib/libcommon.a”)
# 下面的例子，只有库名，cmake会自动去所包含的目录搜索
link_libraries(boost_chrono)
link_libraries(pthread)
link_libraries(stdc++)
link_libraries(boost_coroutine)
link_libraries(ssl)
link_libraries(crypto)

# 设置编译版本 c++ 11
add_compile_options(-std=c++11)
# 编译器优化设置
add_compile_options(-O3)

# 指定生成目标
#ADD_EXECUTABLE(main ${DIR_SRCS})
ADD_EXECUTABLE(../build/bybit ./bybit.cpp)