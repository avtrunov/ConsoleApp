#include "Chatbot\CmdChangeTask.h"

json::value CmdChangeTask::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.Update("Task")
		.Set("Description ='" + task.description + "'")
		.Where("Id =" + std::to_string(task.id))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The task " + std::to_wstring(task.id) + L" description has been changed.\n");
	return result;
}