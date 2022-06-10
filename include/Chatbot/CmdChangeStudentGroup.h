#pragma once
#include "Chatbot/CommandSQL.h"

class CmdChangeStudentGroup : public CommandSQL
{
private:
	const int studentId;
	const std::string groupName;
public:
	CmdChangeStudentGroup(const Table::Student& stud, const Table::Group& gr) :studentId(stud.id), groupName(gr.name) {}
	CmdChangeStudentGroup(const CmdChangeStudentGroup&) = delete;
	CmdChangeStudentGroup& operator=(const CmdChangeStudentGroup&) = delete;
	~CmdChangeStudentGroup() = default;

	json::value Execute(Database& database) override;
};