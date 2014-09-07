add_executable(mAIDA.exe mAIDA.cxx)
target_link_libraries(mAIDA.exe mAIDA ${ROOT_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})