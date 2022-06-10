#pragma once
#include "Chatbot/CommandSQL.h"

class CmdChangeStudentName : public CommandSQL
{
private:
	const Table::Student student;
public:
	CmdChangeStudentName(const Table::Student& stud) :student(stud) {}
	CmdChangeStudentName(const CmdChangeStudentName&) = delete;
	CmdChangeStudentName& operator=(const CmdChangeStudentName&) = delete;
	~CmdChangeStudentName() = default;

	json::value Execute(Database& database) override;
};