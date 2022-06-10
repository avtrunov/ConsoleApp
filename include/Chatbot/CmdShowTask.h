#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowTask : public CommandSQL
{
private:
	const int taskId;
public:
	CmdShowTask(const Table::Task& task) :taskId(task.id) {}
	CmdShowTask(const CmdShowTask&) = delete;
	CmdShowTask& operator=(const CmdShowTask&) = delete;
	~CmdShowTask() = default;

	json::value Execute(Database& database) override;
};