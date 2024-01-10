cmake_minimum_required(VERSION 3.10)

project(ClassTest)

find_package(OpenCV REQUIRED)

add_executable(class_test class_test.cpp)
target_link_libraries(class_test PRIVATE ${OpenCV_LIBS})
