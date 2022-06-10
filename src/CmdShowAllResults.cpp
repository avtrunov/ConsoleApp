#include "Chatbot\CmdShowAllResults.h"

json::value CmdShowAllResults::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Student.LName, Student.Initials,"
			"Groups.Name AS GroupName,"
			"Variant.TaskId, Variant.VariantId, Variant.Description,"
			"Test.Status, Test.Commentary, MAX(CommitDate) as Date, Test.GitURL")
		.From("Test")
		.Join("Variant").On("Variant.Id = Test.TaskId")
		.Join("Student").On("Student.Id = Test.StudentId")
		.Join("Groups").On("Groups.Id = Student.GroupId")
		.GroupBy("Test.StudentId, Test.TaskId")
		.OrderBy("Groups.Id, Student.LName")
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
			errMessage = "The results of testing do not exist. The testing might not have been done\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("table"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}