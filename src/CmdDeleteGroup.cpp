#include "Chatbot\CmdDeleteGroup.h"

json::value CmdDeleteGroup::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Begin().Terminate()
		.Update("Student")
		.Set("GroupId = NULL")
		.Where("GroupId")
		.In(
			BuilderSQL{}.Select("Id")
			.From("Groups")
			.Where("Name LIKE '" + groupName + "'")
			.Build()).Terminate()
		.Delete()
		.From("Groups")
		.Where("Name LIKE '" + groupName + "'").Terminate()
		.Commit().Terminate()
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The group " + to_string_t(groupName) + L" has been deleted from the database.\n");
	return result;
}