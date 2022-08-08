# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\a5_5_913_Goia_Alexia_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\a5_5_913_Goia_Alexia_autogen.dir\\ParseCache.txt"
  "a5_5_913_Goia_Alexia_autogen"
  )
endif()
