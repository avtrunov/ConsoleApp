file(GLOB Chatbot_h "../include/Chatbot/*.h")
file(GLOB Chatbot_src "*.cpp")
#list(REMOVE_ITEM Chatbot_src "ChatbotConfig.h.in")

add_library(Chatbot_library ${Chatbot_src} ${Chatbot_h})

target_include_directories(Chatbot_library PUBLIC ../include)

target_link_libraries(Chatbot_library 
PRIVATE
cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_brotli_internal
unofficial::sqlite3::sqlite3
ZLIB::ZLIB
opencv_highgui opencv_core
ftxui::dom ftxui::screen ftxui::component
tabulate::tabulate)

#Setting configuration file that includes path to the chatbot's additional directories
set(IMAGE_PATH \"${PROJECT_BINARY_DIR}/utility/image/\")
set(TABLE_PATH \"${PROJECT_BINARY_DIR}/utility/table/\")
set(DATABASE_PATH \"${PROJECT_BINARY_DIR}/utility/database/database.db\")
message("Database path has been set = ${DATABASE_PATH}")
configure_file(ChatbotConfig.h.in ChatbotConfig.h)
target_include_directories(Chatbot_library PUBLIC "${PROJECT_BINARY_DIR}/src")