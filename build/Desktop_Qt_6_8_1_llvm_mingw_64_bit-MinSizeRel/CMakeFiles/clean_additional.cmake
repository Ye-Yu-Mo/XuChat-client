# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "MinSizeRel")
  file(REMOVE_RECURSE
  "CMakeFiles\\XuChat-client_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\XuChat-client_autogen.dir\\ParseCache.txt"
  "XuChat-client_autogen"
  )
endif()
