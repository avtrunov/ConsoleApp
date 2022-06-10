#include "Chatbot/ConsolePrinter.h"

ConsolePrinter::ConsolePrinter()
{
	Output(std::stringstream("Press <Enter> to create a request\n"));
}

void ConsolePrinter::Input(const unsigned id, std::string& str)
{
	do
	{
		if (_getch() == 13)
		{
			std::lock_guard<std::mutex> lock(mtx);
			std::cout << "\n>#" << std::setfill('0') << std::setw(4) << id << ": ";
			std::getline(std::cin, str);
			boost::trim_if(str, boost::is_any_of(" \t\n\r"));
		}
	} while (str.empty());
}

void ConsolePrinter::Output(const std::stringstream& buffer)
{
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << buffer.rdbuf();
}

void ConsolePrinter::Run()
{}