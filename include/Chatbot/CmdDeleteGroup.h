#pragma once
#include "Chatbot/CommandSQL.h"

class CmdDeleteGroup : public CommandSQL
{
private:
	const std::string groupName;
public:
	CmdDeleteGroup(const Table::Group& group) :groupName(group.name) {}
	CmdDeleteGroup(const CmdDeleteGroup&) = delete;
	CmdDeleteGroup& operator=(const CmdDeleteGroup&) = delete;
	~CmdDeleteGroup() = default;

	json::value Execute(Database& database) override;
};