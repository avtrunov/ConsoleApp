#include "Chatbot\CmdAddTask.h"

json::value CmdAddTask::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.InsertInto("Task")
		.Values(std::to_string(task.id) + ",'" + task.description + "'")
		.Build());

	if (!success)
	{
		errMessage = "This task already exists.\n";
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The task " + std::to_wstring(task.id) + L" has been added to the database.\n");
	return result;
}