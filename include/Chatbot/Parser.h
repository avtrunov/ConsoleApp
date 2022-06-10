#pragma once
#include "Chatbot/CommandHeaderList.h"
#include "Chatbot/TableData.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

class Parser
{
private:
	TableData table;
protected:
	std::string errMessage = "";
	std::unique_ptr<CommandSQL> Adding(std::string& message);
	std::unique_ptr<CommandSQL> Changing(std::string& message);
	std::unique_ptr<CommandSQL> Deleting(std::string& message);
	std::unique_ptr<CommandSQL> Results(std::string& message);
	std::unique_ptr<CommandSQL> Showing(std::string& message);
	std::unique_ptr<CommandSQL> Get(std::string& message);
	bool HandleNumber(int& num, const std::string& str);
	bool AddTask(const std::string& message);
	bool AddVariant(const std::string& message);
	bool AddGroup(const std::string& message);
	bool AddStudent(const std::string& message);
	bool ChangeTask(const std::string& message);
	bool ChangeVariant(const std::string& message);
	bool ChangeGroup(const std::string& message);
	bool ChangeStudent(const std::string&& arg, const std::string& message);
	bool DeleteTask(const std::string& message);
	bool DeleteStudent(const std::string& message);
	bool DeleteGroup(const std::string& message);
	bool DeleteVariant(const std::string& message);
	bool DeleteStudentsFromGroup(const std::string& message);
	bool ShowTask(const std::string& message);
	bool ShowVariant(const std::string& message);
	bool ShowVariantByTask(const std::string& message);
	bool ShowStudentsFromGroup(const std::string& message);
	bool ShowGroups(const std::string& message);
	bool ShowAllTasks(const std::string& message);
	bool ShowAllVariants(const std::string& message);
	bool ShowAllStudents(const std::string& message);
	bool ResultsByTask(const std::string& message);
	bool ResultsByStudent(const std::string& message);
	bool ResultsByStudentTask(const std::string& message);
	bool AllResults(const std::string& message);
	bool GetCameraFrame(const std::string& message);
public:
	virtual std::unique_ptr<CommandSQL> Parse(std::string& message) = 0;
	virtual std::string ErrorMessage() const noexcept;

	Parser() = default;
	virtual ~Parser() = default;
};

//добавить обработку пустых сообщений 