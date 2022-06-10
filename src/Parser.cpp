#include "Chatbot\Parser.h"
namespace bst = boost;

std::string Parser::ErrorMessage() const noexcept
{
	return errMessage;
}

bool Parser::HandleNumber(int& num, const std::string& str)
{
	try
	{
		num = std::stoi(str);
	}
	catch (std::out_of_range& e)
	{
		errMessage = "Argument out of range.\n";
		return false;
	}
	return true;
}

//---------------------ADDING OPERATIONS---------------------------------------------------------

bool Parser::AddTask(const std::string& message)
{
	bst::regex reg("^add task (\\d+) [\'|\"]([\\w\\s\\-]+)[\'|\"]$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()))
			return false;
		table.task.description = what[2].str();
		return true;
	}
	return false;
}

bool Parser::AddVariant(const std::string& message)
{
	bst::regex reg("^add task (\\d+) variant (\\d+) [\'|\"]([\\w\\s\\-]+)[\'|\"]$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()) || !HandleNumber(table.variant.id, what[2].str()))
			return false;
		table.variant.description = what[3].str();
		return true;
	}
	return false;
}

bool Parser::AddGroup(const std::string& message)
{
	bst::regex reg("^add group ([\\w\\-]+)$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.group.name = what[1].str();
		return true;
	}
	return false;
}

bool Parser::AddStudent(const std::string& message)
{
	bst::regex reg("^add student (\\w+) (\\w+)\\s?([\\w\\-]+)?$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.student.lastName = what[1].str();
		table.student.initials = what[2].str();
		table.group.name = what[3].str();
		return true;
	}
	return false;
}

std::unique_ptr<CommandSQL> Parser::Adding(std::string& message)
{
	if (AddTask(message))
	{
		return std::make_unique<CmdAddTask>(table.task);
	}
	else if (AddVariant(message))
	{
		return std::make_unique<CmdAddVariant>(table.task, table.variant);
	}
	else if (AddGroup(message))
	{
		return std::make_unique<CmdAddGroup>(table.group);
	}
	else if (AddStudent(message))
	{
		return std::make_unique<CmdAddStudent>(table.group, table.student);
	}
	return nullptr;
}

//--------------------------------CHANGING OPERATIONS-----------------------------------------------------------------------------

bool Parser::ChangeTask(const std::string& message)
{
	bst::regex reg("^change task (\\d+) [\'|\"]([\\w\\s\\-]+)[\'|\"]$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()))
			return false;
		table.task.description = what[2].str();
		return true;
	}
	return false;
}

bool Parser::ChangeVariant(const std::string& message)
{
	bst::regex reg("^change task (\\d+) variant (\\d+) [\'|\"]([\\w\\s\\-]+)[\'|\"]$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()) || !HandleNumber(table.variant.id, what[2].str()))
			return false;
		table.variant.description = what[3].str();
		return true;
	}
	return false;
}

bool Parser::ChangeGroup(const std::string& message)
{
	bst::regex reg("^change group (\\d+) name (?:to )?([\\w\\-]+)$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.group.id, what[1].str()))
			return false;
		table.group.name = what[2].str();
		return true;
	}
	return false;
}

bool Parser::ChangeStudent(const std::string&& arg, const std::string& message)
{
	bst::regex reg("^change student (\\d+) " + arg + " (?:to )?([\\w\\-]+)$", bst::regex::perl | bst::regex::icase);
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.student.id, what[1].str()))
			return false;
		table.student.lastName = what[2].str();
		table.student.initials = what[2].str();
		table.group.name = what[2].str();
		return true;
	}
	return false;
}

std::unique_ptr<CommandSQL> Parser::Changing(std::string& message)
{
	if (ChangeTask(message))
	{
		return std::make_unique<CmdChangeTask>(table.task);
	}
	else if (ChangeVariant(message))
	{
		return std::make_unique<CmdChangeVariant>(table.task, table.variant);
	}
	else if (ChangeGroup(message))
	{
		return std::make_unique<CmdChangeGroup>(table.group);
	}
	else if (ChangeStudent("last name",message))
	{
		return std::make_unique<CmdChangeStudentName>(table.student);
	}
	else if (ChangeStudent("initials", message))
	{
		return std::make_unique<CmdChangeStudentInitials>(table.student);
	}
	else if (ChangeStudent("group", message))
	{
		return std::make_unique<CmdChangeStudentGroup>(table.student, table.group);
	}
	return nullptr;
}

//-----------------------DELETING OPERATIONS----------------------------------------------------------------

bool Parser::DeleteTask(const std::string& message)
{
	bst::regex reg("^delete task ([\\w\\-]+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::DeleteStudent(const std::string& message)
{
	bst::regex reg("^delete student ([\\w\\-]+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.student.id, what[1].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::DeleteGroup(const std::string& message)
{
	bst::regex reg("^delete group ([\\w\\-]+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.group.name = what[1].str();
		return true;
	}
	return false;
}

bool Parser::DeleteVariant(const std::string& message)
{
	bst::regex reg("^delete task (\\d+) variant (\\d+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()) || !HandleNumber(table.variant.id, what[2].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::DeleteStudentsFromGroup(const std::string& message)
{
	bst::regex reg("^delete students (?:from )?group ([\\w\\-]+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.group.name = what[1].str();
		return true;
	}
	return false;
}

std::unique_ptr<CommandSQL> Parser::Deleting(std::string& message)
{
	if (DeleteTask(message))
	{
		return std::make_unique<CmdDeleteTask>(table.task);
	}
	else if (DeleteStudent(message))
	{
		return std::make_unique<CmdDeleteStudent>(table.student);
	}
	else if (DeleteGroup(message))
	{
		return std::make_unique<CmdDeleteGroup>(table.group);
	}
	else if (DeleteVariant(message))
	{
		return std::make_unique<CmdDeleteVariant>(table.task, table.variant);
	}
	else if (DeleteStudentsFromGroup(message))
	{
		return std::make_unique<CmdDeleteStudentsFromGroup>(table.group);
	}
	return nullptr;
}

//-------------------------------------SHOWING OPERATIONS--------------------------------------------------------

bool Parser::ShowTask(const std::string& message)
{
	bst::regex reg("^show task (\\d+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::ShowVariant(const std::string& message)
{
	bst::regex reg("^show task (\\d+) variant (\\d+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()) || !HandleNumber(table.variant.id, what[2].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::ShowVariantByTask(const std::string& message)
{
	bst::regex reg("^show task (\\d+) variant all$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::ShowStudentsFromGroup(const std::string& message)
{
	bst::regex reg("^show students (?:from )?group ([\\w\\-]+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.group.name = what[1].str();
		return true;
	}
	return false;
}

bool Parser::ShowGroups(const std::string& message)
{
	return bst::iequals(message, "show all groups");
}

bool Parser::ShowAllTasks(const std::string& message)
{
	return bst::iequals(message, "show all tasks");
}

bool Parser::ShowAllVariants(const std::string& message)
{
	return bst::iequals(message, "show all variants");
}

bool Parser::ShowAllStudents(const std::string& message)
{
	return bst::iequals(message, "show all students");
}

std::unique_ptr<CommandSQL> Parser::Showing(std::string& message)
{
	if (ShowTask(message))
	{
		return std::make_unique<CmdShowTask>(table.task);
	}
	else if (ShowVariantByTask(message))
	{
		return std::make_unique<CmdShowVariantsByTask>(table.task);
	}
	else if (ShowStudentsFromGroup(message))
	{
		return std::make_unique<CmdShowStudentsFromGroup>(table.group);
	}
	else if (ShowVariant(message))
	{
		return std::make_unique<CmdShowVariant>(table.task, table.variant);
	}
	else if (ShowGroups(message))
	{
		return std::make_unique<CmdShowGroups>();
	}
	else if (ShowAllTasks(message))
	{
		return std::make_unique<CmdShowAllTasks>();
	}
	else if (ShowAllVariants(message))
	{
		return std::make_unique<CmdShowAllVariants>();
	}
	else if (ShowAllStudents(message))
	{
		return std::make_unique<CmdShowAllStudents>();
	}
	return nullptr;
}

//-------------------------TEST RESULTS OPERATIONS----------------------------------------------

bool Parser::ResultsByTask(const std::string& message)
{
	bst::regex reg("^results (?:of )?task (\\d+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		if (!HandleNumber(table.task.id, what[1].str()))
			return false;
		return true;
	}
	return false;
}

bool Parser::ResultsByStudent(const std::string& message)
{
	bst::regex reg("^results (?:of )?student (\\w+) (\\w+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.student.lastName = what[1].str();
		table.student.initials = what[2].str();
		return true;
	}
	return false;
}

bool Parser::ResultsByStudentTask(const std::string& message)
{
	bst::regex reg("^results (?:of )?student (\\w+) (\\w+) (?:of )?task (\\d+)$");
	bst::smatch what;
	if (bst::regex_match(message, what, reg))
	{
		table.student.lastName = what[1].str();
		table.student.initials = what[2].str();
		if (!HandleNumber(table.task.id, what[3].str()))
			return false;		
		return true;
	}
	return false;
}

bool Parser::AllResults(const std::string& message)
{
	return bst::regex_match(message, bst::regex("results (?:of )?all tasks"));
}

std::unique_ptr<CommandSQL> Parser::Results(std::string& message)
{
	if (ResultsByTask(message))
	{
		return std::make_unique<CmdShowResultsByTask>(table.task);
	}
	else if (ResultsByStudent(message))
	{
		return std::make_unique<CmdShowResultsByStudent>(table.student);
	}
	else if (ResultsByStudentTask(message))
	{
		return std::make_unique<CmdShowResultByStudentTask>(table.student, table.task);
	}
	else if (AllResults(message))
	{
		return std::make_unique<CmdShowAllResults>();
	}
	return nullptr;
}

//----------------------GETTING OPERATIONS------------------------------------------------------

bool Parser::GetCameraFrame(const std::string& message)
{
	return bst::iequals(message, "get camera frame");
}

std::unique_ptr<CommandSQL> Parser::Get(std::string& message)
{
	if (GetCameraFrame(message))
	{
		return std::make_unique<CmdGetCameraFrame>();
	}
	errMessage += "Cannot parse data.\n";
	return nullptr;
}