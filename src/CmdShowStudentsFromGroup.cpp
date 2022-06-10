#include "Chatbot\CmdShowStudentsFromGroup.h"

json::value CmdShowStudentsFromGroup::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.Select("Student.Id,Student.LName, Student.Initials, Groups.Name AS GroupName")
		.From("Student")
		.Join("Groups")
		.On("Student.GroupId = Groups.Id")
		.Where("Groups.Name LIKE '" + groupName + "'")
		.OrderBy("Student.LName")
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}
	else
	{
		if (answer.empty())
		{
			errMessage += "The student list of the group " + groupName + " is empty.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("table"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}