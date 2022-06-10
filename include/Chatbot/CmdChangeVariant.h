#pragma once
#include "Chatbot/CommandSQL.h"

class CmdChangeVariant : public CommandSQL
{
private:
	const int taskId;
	const Table::Variant variant;
public:
	CmdChangeVariant(Table::Task& tsk, Table::Variant& var) :taskId(tsk.id), variant(var) {}
	CmdChangeVariant(const CmdChangeVariant&) = delete;
	CmdChangeVariant& operator=(const CmdChangeVariant&) = delete;
	~CmdChangeVariant() = default;

	json::value Execute(Database& database) override;
};