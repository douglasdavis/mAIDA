cmake_minimum_required(VERSION 2.8)
project(mAIDA)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_CXX_FLAGS "-O2 -std=c++1y -Wall")
set(CMAKE_SHARED_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories("${Boost_INCLUDE_DIRS}")
link_directories("${Boost_LIBRARY_DIR}")

find_package(ROOT REQUIRED)
include_directories("${ROOT_INCLUDE_DIR}")
link_directories("${ROOT_LIBRARY_DIR}")

option(ROOT6 "ROOT6" OFF)
if(ROOT6)
  message("-- ROOT 6 CMake option set ON")
else()
  message("-- ROOT 6 CMake option set OFF (default even for ROOT version 6 installation)")
endif()

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/include")

ROOT_GENERATE_DICTIONARY(
  mAIDAclassesdict
  include/mAIDA/Reader.h
  include/mAIDA/PhysicsObject.h
  include/mAIDA/Jet.h
  include/mAIDA/Lepton.h
  include/mAIDA/FinalState.h
  include/mAIDA/Swizzler.h
  include/mAIDA/VariableFiller.h
  include/mAIDA/MVASigBkg.h
  include/mAIDA/LeptonPair.h
  include/mAIDA/MVARunner.h
  LINKDEF include/mAIDA/LinkDef.h
  )

file(GLOB mAIDAclasses_src
  "src/*.cxx"
  )

add_library(
  mAIDAclasses SHARED
  ${mAIDAclasses_src}
  mAIDAclassesdict
  )

target_link_libraries(mAIDAclasses ${ROOT_LIBRARIES} TMVA)

install(DIRECTORY include/mAIDA DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
install(TARGETS mAIDAclasses DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
install(DIRECTORY config DESTINATION "${CMAKE_INSTALL_PREFIX}")
if(ROOT6)
  install(FILES ${CMAKE_BINARY_DIR}/mAIDAclassesdict_rdict.pcm DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif()

add_subdirectory(producers)
add_subdirectory(readers)
add_subdirectory(sb)
