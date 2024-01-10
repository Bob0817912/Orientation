set(SOURCES
Inheritance.hpp
Polymorphism_dynamic.hpp
Polymorphism_static.hpp
)
add_library(DemoFunctions ${SOURCES})
set_target_properties(DemoFunctions PROPERTIES LINKER_LANGUAGE CXX)