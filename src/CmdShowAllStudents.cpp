#include "Chatbot\CmdShowAllStudents.h"

json::value CmdShowAllStudents::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Student.Id,Student.LName, Student.Initials, Groups.Name AS GroupName")
		.From("Student")
		.LeftJoin("Groups")
		.On("Student.GroupId = Groups.Id")
		.OrderBy("Groups.Id, Student.LName")
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
			errMessage = "The student list is empty.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("table"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}