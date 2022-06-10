#include "Chatbot\ParserTeacher.h"
namespace bst = boost;


std::unique_ptr<CommandSQL> ParserTeacher::Parse(std::string& message)
{
	if (bst::istarts_with(message, "add "))
	{
		return Adding(message);
	}
	else if (bst::istarts_with(message, "change "))
	{
		return Changing(message);
	}
	else if (bst::istarts_with(message, "delete "))
	{
		return Deleting(message);
	}
	else if (bst::istarts_with(message, "show "))
	{
		return Showing(message);
	}
	else if (bst::istarts_with(message, "results "))
	{
		return Results(message);
	}
	else if (bst::istarts_with(message, "get "))
	{
		return Get(message);
	}
	errMessage += "Unknown command.\n";
	return nullptr;
}