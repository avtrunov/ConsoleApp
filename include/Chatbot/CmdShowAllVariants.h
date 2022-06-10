#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowAllVariants : public CommandSQL
{
public:
	CmdShowAllVariants() = default;
	CmdShowAllVariants(const CmdShowAllVariants&) = delete;
	CmdShowAllVariants& operator=(const CmdShowAllVariants&) = delete;
	~CmdShowAllVariants() = default;

	json::value Execute(Database& database) override;
};