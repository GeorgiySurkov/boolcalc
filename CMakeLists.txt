cmake_minimum_required(VERSION 3.21)

project(boolcalc)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
        boolcalc
        boolcalc.cpp
        boolexpr.h
        boolexpr.cpp
        avltree.h
        errors.h
        formulaenode.h
        formulaenode.cpp
        lib/avl_map.h
        lib/cstring.h
        lib/cstring.cpp
        lib/functional.h
        lib/utility.h
        lib/vector.h
        helpers.h)
