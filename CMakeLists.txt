cmake_minimum_required(VERSION 2.8)
project(mAIDA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall")
set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

option(ROOT6 "ROOT6" OFF)
if(ROOT6)
  message("-- ROOT 6 set ON")
else()
  message("-- ROOT 6 set OFF")
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories("${Boost_INCLUDE_DIRS}")
link_directories("${Boost_LIBRARY_DIR}")

find_package(ROOT REQUIRED)
include_directories("${ROOT_INCLUDE_DIR}")
link_directories("${ROOT_LIBRARY_DIR}")

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/include")

ROOT_GENERATE_DICTIONARY(
  mAIDAdict
  include/Reader.h
  include/PhysicsObject.h
  include/Jet.h
  include/Lepton.h
  include/FinalState.h
  include/Swizzler.h
  include/VariableFiller.h
  include/MVASigBkg.h
  LINKDEF include/LinkDef.h
  )

file(GLOB mAIDA_src
  "src/*.cxx"
  )

add_library(
  mAIDA SHARED
  ${mAIDA_src}
  mAIDAdict
  )

target_link_libraries(mAIDA ${ROOT_LIBRARIES} TMVA)

add_subdirectory(producers)
add_subdirectory(readers)
