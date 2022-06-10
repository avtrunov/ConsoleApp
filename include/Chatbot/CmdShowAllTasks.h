#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowAllTasks : public CommandSQL
{
public:
	CmdShowAllTasks() = default;
	CmdShowAllTasks(const CmdShowAllTasks&) = delete;
	CmdShowAllTasks& operator=(const CmdShowAllTasks&) = delete;
	~CmdShowAllTasks() = default;

	json::value Execute(Database& database) override;
};