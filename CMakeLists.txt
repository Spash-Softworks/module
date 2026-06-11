cmake_minimum_required(VERSION 3.20)
project(femboyware CXX)

set(MODULE_NAME "rat")
set(LOADER_NAME "loader")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "build in x64 retard")
endif()

# out
set(OUT_DIR ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUT_DIR})

# module
add_library(module SHARED
    module/entry.cpp
    module/sdk/scheduler/scheduler.cpp
    module/sdk/tphandler/tphandler.cpp
    module/sdk/execution/execution.cpp
)

target_include_directories(module PRIVATE
    ${CMAKE_SOURCE_DIR}/module
)

target_compile_definitions(module PRIVATE
    WIN32
    _WINDOWS
    _USRDLL
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

target_link_libraries(module PRIVATE
    kernel32
    user32
    luau
)

set_target_properties(module PROPERTIES OUTPUT_NAME ${MODULE_NAME})

# luau
set(LUAU_DIR ${CMAKE_SOURCE_DIR}/module/libs/luau)

file(GLOB_RECURSE LUAU_SOURCES
    ${LUAU_DIR}/VM/src/*.cpp
    ${LUAU_DIR}/Compiler/src/*.cpp
    ${LUAU_DIR}/Ast/src/*.cpp
    ${LUAU_DIR}/Bytecode/src/*.cpp
    ${LUAU_DIR}/Common/src/*.cpp
    ${LUAU_DIR}/CodeGen/src/*.cpp
)

add_library(luau STATIC ${LUAU_SOURCES})

target_include_directories(luau PUBLIC
    ${LUAU_DIR}/VM/include
    ${LUAU_DIR}/Compiler/include
    ${LUAU_DIR}/Ast/include
    ${LUAU_DIR}/Bytecode/include
    ${LUAU_DIR}/Common/include
    ${LUAU_DIR}/CodeGen/include
)

target_compile_definitions(luau PRIVATE
    WIN32
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

# shitty injector
add_executable(loader
    inj/entry.cpp
)

target_compile_definitions(loader PRIVATE
    WIN32
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

target_link_libraries(loader PRIVATE
    kernel32
    user32
    psapi
)

set_target_properties(loader PROPERTIES OUTPUT_NAME ${LOADER_NAME})

# msvc flags
if(MSVC)
    foreach(tgt module loader luau)
        target_compile_options(${tgt} PRIVATE /W3 /MP /EHsc)
        set_target_properties(${tgt} PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreaded"
        )
    endforeach()
endif()
