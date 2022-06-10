add_executable(ChatbotServer server.cpp)
add_executable(ChatbotClientConsole clientConsole.cpp)
add_executable(ChatbotClientFTXUI clientFTXUI.cpp)
add_executable(SetDatabase set_database.cpp)

target_compile_features(ChatbotServer PRIVATE cxx_std_17)
target_compile_features(ChatbotClientConsole PRIVATE cxx_std_17)
target_compile_features(ChatbotClientFTXUI PRIVATE cxx_std_17)
target_compile_features(SetDatabase PRIVATE cxx_std_17)

target_link_libraries(ChatbotServer PRIVATE Chatbot_library)
target_link_libraries(ChatbotClientConsole PRIVATE Chatbot_library)
target_link_libraries(ChatbotClientFTXUI PRIVATE Chatbot_library)
target_link_libraries(SetDatabase PRIVATE Chatbot_library)

#Run the executable to install the chatbot's database after build
add_custom_command(
    TARGET SetDatabase
    POST_BUILD
    COMMAND SetDatabase)