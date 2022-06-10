#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowVariantsByTask : public CommandSQL
{
private:
	const int taskId;
public:
	CmdShowVariantsByTask(Table::Task& tsk): taskId(tsk.id) {}
	CmdShowVariantsByTask(const CmdShowVariantsByTask&) = delete;
	CmdShowVariantsByTask& operator=(const CmdShowVariantsByTask&) = delete;
	~CmdShowVariantsByTask() = default;

	json::value Execute(Database& database) override;
};