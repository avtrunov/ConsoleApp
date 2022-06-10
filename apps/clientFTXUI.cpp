#include "Chatbot/ClientLogic.h"
#include "Chatbot/FTXUI.h"

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

	ClientLogic<FTXUI> api;
	try
	{
		api.Execute();
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
		return 3;
	}
	_getch();
	return 0;
}