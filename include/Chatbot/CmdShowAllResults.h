#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowAllResults : public CommandSQL
{
public:
	CmdShowAllResults() = default;
	CmdShowAllResults(const CmdShowAllResults&) = delete;
	CmdShowAllResults& operator=(const CmdShowAllResults&) = delete;
	~CmdShowAllResults() = default;

	json::value Execute(Database& database) override;
};