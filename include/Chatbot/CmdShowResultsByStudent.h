#pragma once 
#include "Chatbot/CommandSQL.h"

class CmdShowResultsByStudent : public CommandSQL
{
private:
	const Table::Student student;
public:
	CmdShowResultsByStudent(const Table::Student stud): student(stud) {}
	CmdShowResultsByStudent(const CmdShowResultsByStudent&) = delete;
	CmdShowResultsByStudent& operator=(const CmdShowResultsByStudent&) = delete;
	~CmdShowResultsByStudent() = default;

	json::value Execute(Database& database) override;
};