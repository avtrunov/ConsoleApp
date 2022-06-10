#include "Chatbot\CmdChangeStudentInitials.h"

json::value CmdChangeStudentInitials::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.Update("Student")
		.Set("Initials ='" + student.initials + "'")
		.Where("Id =" + std::to_string(student.id))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The student's initials has been changed.\n");
	return result;
}