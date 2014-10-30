add_executable(sb sb.cxx)
target_link_libraries(sb mAIDAlib ${ROOT_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY} TMVA)
