#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowVariant : public CommandSQL
{
private:
	const int taskId;
	const int variantId;
public:
	CmdShowVariant(Table::Task& tsk, Table::Variant& var):taskId(tsk.id), variantId(var.id) {}
	CmdShowVariant(const CmdShowVariant&) = delete;
	CmdShowVariant& operator=(const CmdShowVariant&) = delete;
	~CmdShowVariant() = default;

	json::value Execute(Database& database) override;
};