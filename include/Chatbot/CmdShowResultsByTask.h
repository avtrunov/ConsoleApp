#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowResultsByTask : public CommandSQL
{
private:
	const int taskNum;
public:
	CmdShowResultsByTask(const Table::Task& tsk) : taskNum(tsk.id) {}
	CmdShowResultsByTask(const CmdShowResultsByTask&) = delete;
	CmdShowResultsByTask& operator=(const CmdShowResultsByTask&) = delete;
	~CmdShowResultsByTask() = default;

	json::value Execute(Database& database) override;
};