# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SheepCalendar_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SheepCalendar_autogen.dir\\ParseCache.txt"
  "SheepCalendar_autogen"
  )
endif()
