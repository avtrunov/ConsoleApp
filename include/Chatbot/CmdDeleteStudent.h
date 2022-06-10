#pragma once
#include "Chatbot/CommandSQL.h"

class CmdDeleteStudent : public CommandSQL
{
private:
	const int studentId;
public:
	CmdDeleteStudent(const Table::Student& stud) :studentId(stud.id) {}
	CmdDeleteStudent(const CmdDeleteStudent&) = delete;
	CmdDeleteStudent& operator=(const CmdDeleteStudent&) = delete;
	~CmdDeleteStudent() = default;

	json::value Execute(Database& database) override;
};