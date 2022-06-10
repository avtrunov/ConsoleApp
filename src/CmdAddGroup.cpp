#include "Chatbot\CmdAddGroup.h"

json::value CmdAddGroup::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.InsertInto("Groups")
		.Values("NULL, '" + groupName + "'")
		.Build());

	if (!success)
	{
		errMessage += "This group already exists.\n";
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The group " + to_string_t(groupName) + L" has been added to the database.\n");
	return result;
}