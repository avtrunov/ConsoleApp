#pragma once
#include "Chatbot/BaseLogic.h"
#include "Chatbot/ParserTeacher.h"
#include "Chatbot/ParserStudent.h"
#include "ChatbotConfig.h"

using Student = ParserStudent;
using Teacher = ParserTeacher;

template<class ParserType>
class Logic : public BaseLogic
{
private:
	Database database;
public:
	Logic();
	Logic(const Logic&) = delete;
	Logic& operator=(const Logic&) = delete;
	~Logic() = default;

	json::value Process(std::string& message) override;
};

template<class ParserType>
Logic<ParserType>::Logic()
{
	if (!database.Open(DATABASE_PATH))
		throw std::domain_error("Cannot access the database on the specified path.\n");
 }


template<class ParserType>
json::value Logic<ParserType>::Process(std::string& message)
{
	json::value errMessage = json::value::parse(U("{\"type\" : \"text\" }"));
	ParserType in;
	auto command = in.Parse(message);
	if (command == nullptr)
	{
		errMessage[U("data")] = json::value(L"Parsing error: " + to_string_t(in.ErrorMessage()));
		return errMessage;
	}

	json::value answer = command->Execute(database);
	if (answer.is_null())
	{
		errMessage[U("data")] = json::value(to_string_t(command->ErrorMessage()));
		return errMessage;
	}
	return answer;
}