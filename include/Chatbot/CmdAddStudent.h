#pragma once
#include "Chatbot/CommandSQL.h"

class CmdAddStudent : public CommandSQL
{
private:
	const Table::Student student;
	const std::string groupName;
public:
	CmdAddStudent(const Table::Group& grp, const Table::Student& stud) :groupName(grp.name), student(stud){}
	CmdAddStudent(const CmdAddStudent&) = delete;
	CmdAddStudent& operator=(const CmdAddStudent&) = delete;
	~CmdAddStudent() = default;

	json::value Execute(Database& database) override;
};