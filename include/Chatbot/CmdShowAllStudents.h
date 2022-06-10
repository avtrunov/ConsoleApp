#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowAllStudents : public CommandSQL
{
public:
	CmdShowAllStudents() = default;
	CmdShowAllStudents(const CmdShowAllStudents&) = delete;
	CmdShowAllStudents& operator=(const CmdShowAllStudents&) = delete;
	~CmdShowAllStudents() = default;

	json::value Execute(Database& database) override;
};