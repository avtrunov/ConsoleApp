#include "Chatbot\CmdDeleteStudentsFromGroup.h"

json::value CmdDeleteStudentsFromGroup::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.Delete()
		.From("Student")
		.Where("GroupId =")(
			BuilderSQL{}.Select("Id")
			.From("Groups")
			.Where("Name LIKE '" + groupName + "'")
			.Build())
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The students of the group " + to_string_t(groupName) + L" has been deleted.\n");
	return result;
}