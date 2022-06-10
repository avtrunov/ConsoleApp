#include "Chatbot\CmdDeleteVariant.h"

json::value CmdDeleteVariant::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Delete()
		.From("Variant")
		.Where("TaskId =" + std::to_string(taskId) + " AND VariantId =" + std::to_string(variantId))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The variant " + std::to_wstring(variantId) + L" of the task " + std::to_wstring(taskId) + L" has been deleted.\n");
	return result;
}