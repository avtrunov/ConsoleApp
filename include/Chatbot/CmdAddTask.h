#pragma once
#include "Chatbot/CommandSQL.h"

class CmdAddTask : public CommandSQL
{
private:
	const Table::Task task;
public:
	CmdAddTask(const Table::Task& tsk) : task(tsk) {}
	CmdAddTask(const CmdAddTask&) = delete;
	CmdAddTask& operator=(const CmdAddTask&) = delete;
	~CmdAddTask() = default;

	json::value Execute(Database& database) override;
};