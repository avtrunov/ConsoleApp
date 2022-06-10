#pragma once
#include "Chatbot/CommandSQL.h"

class CmdDeleteStudentsFromGroup : public CommandSQL
{
private:
	const std::string groupName;
public:
	CmdDeleteStudentsFromGroup(const Table::Group& gr) :groupName(gr.name) {}
	CmdDeleteStudentsFromGroup(const CmdDeleteStudentsFromGroup&) = delete;
	CmdDeleteStudentsFromGroup& operator=(const CmdDeleteStudentsFromGroup&) = delete;
	~CmdDeleteStudentsFromGroup() = default;

	json::value Execute(Database& database) override;
};