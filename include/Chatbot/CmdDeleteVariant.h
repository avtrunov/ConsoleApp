#pragma once
#include "Chatbot/CommandSQL.h"

class CmdDeleteVariant : public CommandSQL
{
private:
	const int taskId;
	const int variantId;
public:
	CmdDeleteVariant(Table::Task& tsk , Table::Variant& var) :taskId(tsk.id), variantId(var.id) {}
	CmdDeleteVariant(const CmdDeleteVariant&) = delete;
	CmdDeleteVariant& operator=(const CmdDeleteVariant&) = delete;
	~CmdDeleteVariant() = default;

	json::value Execute(Database& database) override;
};