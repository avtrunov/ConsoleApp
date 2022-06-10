#pragma once
#include "Chatbot/CommandSQL.h"

class CmdDeleteTask : public CommandSQL
{
private:
	const int taskNum;
public:
	CmdDeleteTask(const Table::Task& tsk) :taskNum(tsk.id) {}
	CmdDeleteTask(const CmdDeleteTask&) = delete;
	CmdDeleteTask& operator=(const CmdDeleteTask&) = delete;
	~CmdDeleteTask() = default;

	json::value Execute(Database& database) override;
};