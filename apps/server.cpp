#include "ChatBot/ChatBotServer.h"

int main()
{
	try
	{
		ServerHandler handler;
		try
		{
			handler.Listening();
			std::cout << "Chatbot version " << Chatbot_VERSION_MAJOR << "." << Chatbot_VERSION_MINOR << ".\nPress ENTER to exit.\n";
			std::cin.get();
		}
		catch (const std::exception& err)
		{
			std::cerr << err.what() << std::endl;
			return 1;
		}
		handler.Shutdown();
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
	return 0;
}