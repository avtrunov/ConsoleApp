#include "Chatbot\CmdShowGroups.h"

json::value CmdShowGroups::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Groups.*, COUNT(Student.GroupId) AS StudentCount")
		.From("Groups")
		.LeftJoin("Student")
		.On("Student.GroupId = Groups.Id")
		.GroupBy("Groups.Id")
		.OrderBy("Groups.Name")
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
			errMessage = "The group list is empty.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("table"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}