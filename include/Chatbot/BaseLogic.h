#pragma once
#include "Chatbot/CommandSQL.h"

class BaseLogic
{
public:
	virtual ~BaseLogic() = default;
	virtual json::value Process(std::string& message) = 0;
};