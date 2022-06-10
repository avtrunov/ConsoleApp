#pragma once
#include "Chatbot/Parser.h"

class ParserStudent :public Parser
{
public:
	ParserStudent() = default;
	ParserStudent(const ParserStudent&) = delete;
	ParserStudent& operator= (const ParserStudent&) = delete;
	~ParserStudent() = default;

	std::unique_ptr<CommandSQL> Parse(std::string& message) override;
};