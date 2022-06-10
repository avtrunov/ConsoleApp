#pragma once
#include "Chatbot/Parser.h"

class ParserTeacher :public Parser
{
public:
	ParserTeacher() = default;
	ParserTeacher(const ParserTeacher&) = delete;
	ParserTeacher& operator= (const ParserTeacher&) = delete;
	~ParserTeacher() = default;

	std::unique_ptr<CommandSQL> Parse(std::string& message) override;
};