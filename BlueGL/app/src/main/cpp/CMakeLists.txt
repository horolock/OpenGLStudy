cmake_minimum_required(VERSION 3.22.1)

project("bluegl")

add_library(
        bluegl-native
        SHARED
        native_renderer.cpp
)

find_library(
        log-lib
        log
)

target_link_libraries(
        bluegl-native
        ${log-lib}
        GLESv2
)