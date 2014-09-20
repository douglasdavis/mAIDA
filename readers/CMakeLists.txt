add_executable(mvareader mvareader.cpp)
target_link_libraries(mvareader ${ROOT_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY} TMVA)
