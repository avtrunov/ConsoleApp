#pragma once
#include "Chatbot/CommandSQL.h"

class CmdChangeTask : public CommandSQL
{
private:
	const Table::Task task;
public:
	CmdChangeTask(const Table::Task& tsk) :task(tsk) {}
	CmdChangeTask(const CmdChangeTask&) = delete;
	CmdChangeTask& operator=(const CmdChangeTask&) = delete;
	~CmdChangeTask() = default;

	json::value Execute(Database& database) override;
};