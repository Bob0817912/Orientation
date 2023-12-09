file(REMOVE_RECURSE
  "libDemoFunctions.a"
  "libDemoFunctions.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/DemoFunctions.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
