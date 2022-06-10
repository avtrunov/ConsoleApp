#include "Chatbot\CmdShowAllVariants.h"

json::value CmdShowAllVariants::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Variant.TaskId, Task.Description, Variant.VariantId, Variant.Description")
		.From("Variant")
		.Join("Task")
		.On("Task.Id = Variant.TaskId")
		.OrderBy("Variant.TaskId, Variant.VariantId")
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
			errMessage = "The task list is empty.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("table"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}