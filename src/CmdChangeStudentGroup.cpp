#include "Chatbot\CmdChangeStudentGroup.h"

json::value CmdChangeStudentGroup::Execute(Database& database)
{
	BuilderSQL sql;

	auto [success, answer] = database.Execute(
		sql.Update("Student")
		.Set("GroupId =")(
			BuilderSQL{}.Select("Id")
			.From("Groups")
			.Where("Name LIKE '" + groupName + "'")
			.Build())
		.Where("Id =" + std::to_string(studentId))
		.Build());

	if (!success)
	{
		errMessage = database.ErrorMessage();
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(L"The student's group name has been changed.\n");
	return result;
}