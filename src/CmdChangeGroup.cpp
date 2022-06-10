#include "Chatbot\CmdChangeGroup.h"

json::value CmdChangeGroup::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Update("Groups")
		.Set("Name ='" + group.name + "'")
		.Where("Id =" + std::to_string(group.id))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The group name has been changed.\n");
	return result;
}