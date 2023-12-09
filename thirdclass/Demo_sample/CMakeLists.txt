cmake_minimum_required (VERSION 2.8)

project (Demo_sample)

aux_source_directory(. DIR_SRCS)

add_subdirectory(include)

include_directories(/home/suibian/Orientation/thirdclass/Demo_sample/include)

add_executable(Demo main.cpp)

target_link_libraries(Demo DemoFunctions)