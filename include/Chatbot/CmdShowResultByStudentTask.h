#pragma once
#include "Chatbot/CommandSQL.h"

class CmdShowResultByStudentTask : public CommandSQL
{
private:
	const int taskNum;
	const Table::Student student;
public:
	CmdShowResultByStudentTask(const Table::Student& stud,const Table::Task& tsk): taskNum(tsk.id), student(stud){}
	CmdShowResultByStudentTask(const CmdShowResultByStudentTask&) = delete;
	CmdShowResultByStudentTask& operator=(const CmdShowResultByStudentTask&) = delete;
	~CmdShowResultByStudentTask() = default;

	json::value Execute(Database& database) override;
};