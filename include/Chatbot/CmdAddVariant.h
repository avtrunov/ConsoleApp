#pragma once
#include "Chatbot/CommandSQL.h"

class CmdAddVariant : public CommandSQL
{
private:
	const int taskId;
	const Table::Variant variant;
public:
	CmdAddVariant(Table::Task& tsk, Table::Variant& var) :taskId(tsk.id), variant(var) {}
	CmdAddVariant(const CmdAddVariant&) = delete;
	CmdAddVariant& operator=(const CmdAddVariant&) = delete;
	~CmdAddVariant() = default;

	json::value Execute(Database& database) override;
};