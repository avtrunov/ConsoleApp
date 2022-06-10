#include "Chatbot\CmdAddVariant.h"

json::value CmdAddVariant::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.InsertInto("Variant")
		.Values("NULL," + std::to_string(taskId) + "," + std::to_string(variant.id) + ",'" + variant.description + "'")
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The variant " + std::to_wstring(variant.id)
		+ L" of the task " + std::to_wstring(taskId) + L" has been added to the database.\n");
	return result;
}