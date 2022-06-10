#include "Chatbot\CmdDeleteTask.h"

json::value CmdDeleteTask::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Begin().Terminate()
		.Delete()
		.From("Task")
		.Where("Id =" + std::to_string(taskNum)).Terminate()
		.Delete()
		.From("Variant")
		.Where("TaskId =" + std::to_string(taskNum)).Terminate()
		.Commit().Terminate()
		.Build());
	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The task " + std::to_wstring(taskNum) + L" has been deleted.\n");
	return result;
}