#include "Chatbot\CmdShowVariant.h"

json::value CmdShowVariant::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("VariantId AS Id, Description")
		.From("Variant")
		.Where("TaskId =" + std::to_string(taskId) + " AND VariantId =" + std::to_string(variantId))
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
			errMessage = "The variant " + std::to_string(variantId) + " of the task " + std::to_string(taskId) + " does not exist.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("table"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}