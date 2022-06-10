#include "Chatbot\CmdDeleteStudent.h"

json::value CmdDeleteStudent::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Delete()
		.From("Student")
		.Where("Id =" + std::to_string(studentId))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The student has been deleted from the database.\n");
	return result;
}