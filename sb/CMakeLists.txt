add_executable(sb sb.cxx)
target_link_libraries(sb mAIDAclasses ${ROOT_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY} TMVA)
