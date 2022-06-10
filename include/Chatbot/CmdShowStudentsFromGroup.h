#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowStudentsFromGroup : public CommandSQL
{
private:
	const std::string groupName;
public:
	CmdShowStudentsFromGroup(const Table::Group& gr) : groupName(gr.name) {}
	CmdShowStudentsFromGroup(const CmdShowStudentsFromGroup&) = delete;
	CmdShowStudentsFromGroup& operator=(const CmdShowStudentsFromGroup&) = delete;
	~CmdShowStudentsFromGroup() = default;

	json::value Execute(Database& database) override;
};