file(GLOB Tests_src "*.cpp")

add_executable(Testing ${Tests_src})

target_compile_features(Testing PRIVATE cxx_std_17)

target_link_libraries(Testing PRIVATE
Chatbot_library
GTest::gtest GTest::gtest_main)