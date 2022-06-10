#pragma once
#include "Chatbot/CommandSQL.h"

class CmdChangeGroup : public CommandSQL
{
private:
	const Table::Group group;
public:
	CmdChangeGroup(const Table::Group& grp) : group(grp) {}
	CmdChangeGroup(const CmdChangeGroup&) = delete;
	CmdChangeGroup& operator=(const CmdChangeGroup&) = delete;
	~CmdChangeGroup() = default;

	json::value Execute(Database& database) override;
};