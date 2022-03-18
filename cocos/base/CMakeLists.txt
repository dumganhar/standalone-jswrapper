cmake_minimum_required(VERSION 3.8)

project(ccbase CXX)

set(module_name ccbase)

set(base_sources)

list(APPEND base_sources
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

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "Source Files" FILES ${base_sources})

add_library(${module_name} ${base_sources})

target_include_directories(${module_name} PUBLIC include)

