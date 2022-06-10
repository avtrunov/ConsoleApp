#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowGroups : public CommandSQL
{
public:
	CmdShowGroups() = default;
	CmdShowGroups(const CmdShowGroups&) = delete;
	CmdShowGroups& operator=(const CmdShowGroups&) = delete;
	~CmdShowGroups() = default;

	json::value Execute(Database& database) override;
};