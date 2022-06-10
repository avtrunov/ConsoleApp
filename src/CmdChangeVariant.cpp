#include "Chatbot\CmdChangeVariant.h"

json::value CmdChangeVariant::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Update("Variant")
		.Set("Description = '" + variant.description + "'")
		.Where("TaskId =" + std::to_string(taskId) + " AND VariantId =" + std::to_string(variant.id))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The variant " + std::to_wstring(variant.id)
		+ L" description of the task " + std::to_wstring(taskId) + L" has been changed.\n");
	return result;
}