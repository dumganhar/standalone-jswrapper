cmake_minimum_required(VERSION 3.8)

project(ccbase CXX)

set(module_name ccbase)

add_library(${module_name}
    include/base/Any.h
    include/base/Log.h
    include/base/Macros.h
    include/base/Optional.h
    include/base/Ptr.h
    include/base/RefCounted.h
    include/base/Variant.h
    include/base/Data.h
    src/Log.cpp
    src/Data.cpp
)
target_include_directories(${module_name} PUBLIC include)

