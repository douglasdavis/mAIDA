add_executable(mAIDA mAIDA.cxx)
target_link_libraries(mAIDA mAIDAclasses ${ROOT_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY} TMVA)
