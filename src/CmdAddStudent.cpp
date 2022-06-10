#include "Chatbot\CmdAddStudent.h"

json::value CmdAddStudent::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.InsertInto("Student")
		.Values("NULL,'" + student.lastName + "','" + student.initials + "',("
			+ BuilderSQL{}.Select("Id").From("Groups").Where("Name LIKE '" + groupName + "'").Build() + ")"
		)
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The student " + to_string_t(student.lastName) + L" " + to_string_t(student.initials) + L" has been added to the database.\n");
	return result;
}