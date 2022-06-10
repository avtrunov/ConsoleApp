#include "Chatbot\ParserStudent.h"
namespace bst = boost;

std::unique_ptr<CommandSQL> ParserStudent::Parse(std::string& message)
{
	if (bst::istarts_with(message, "show "))
	{
		return Showing(message);
	}
	errMessage += "Unknown command.\n";
	return nullptr;
}