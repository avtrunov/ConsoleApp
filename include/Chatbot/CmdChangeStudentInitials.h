#pragma once
#include "Chatbot/CommandSQL.h"

class CmdChangeStudentInitials : public CommandSQL
{
private:
	const Table::Student student;
public:
	CmdChangeStudentInitials(const Table::Student& stud) : student(stud) {}
	CmdChangeStudentInitials(const CmdChangeStudentInitials&) = delete;
	CmdChangeStudentInitials& operator=(const CmdChangeStudentInitials&) = delete;
	~CmdChangeStudentInitials() = default;

	json::value Execute(Database& database) override;
};