#pragma once
#include "Chatbot/CommandSQL.h"

class CmdAddGroup : public CommandSQL
{
private:
	const std::string groupName;
public:
	CmdAddGroup(Table::Group& group) :groupName(group.name) { }
	CmdAddGroup(const CmdAddGroup&) = delete;
	CmdAddGroup& operator=(const CmdAddGroup&) = delete;
	~CmdAddGroup() = default;

	json::value Execute(Database& database) override;
};