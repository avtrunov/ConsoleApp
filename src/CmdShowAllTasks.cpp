#include "Chatbot\CmdShowAllTasks.h"

json::value CmdShowAllTasks::Execute(Database& database)
{
	std::this_thread::sleep_for(std::chrono::seconds(15));
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("*")
		.From("Task")
		.OrderBy("Id")
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