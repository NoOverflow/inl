cmake_minimum_required(VERSION 3.17)
project(inl)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

# source files
set(SOURCES ${SOURCES}
    "inl/include/Core/Socket.hpp"

    "inl/src/Core/Socket.cpp"
)

# compile options
set(compile_flags
    _CRT_SECURE_NO_WARNINGS
    GLM_FORCE_SILENT_WARNINGS
    IGE_OPENGL
)

# static library
add_library(inl STATIC ${SOURCES})
target_include_directories(inl
    PRIVATE "inl/include"
    SYSTEM INTERFACE "inl/include"
)
set_target_properties(inl
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)
target_compile_options(inl
    PRIVATE
        $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:-Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4103>
)
target_compile_definitions(inl PUBLIC ${compile_flags})
