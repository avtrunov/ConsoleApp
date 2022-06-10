#include "Chatbot\CmdShowResultsByStudent.h"

json::value CmdShowResultsByStudent::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Variant.TaskId, Task.Description,"
			"Variant.VariantId, Variant.Description,"
			"Test.Status, Test.Commentary, Test.CommitDate, Test.GitURL")
		.From("Test")
		.Join("Task").On("Task.Id = Variant.TaskId")
		.Join("Variant").On("Variant.Id = Test.TaskId")
		.Join("Student").On("Student.Id = Test.StudentId")
		.Where("Student.LName LIKE '" + student.lastName + "' AND Student.Initials LIKE '" + student.initials + "'")
		.GroupBy("Test.TaskId")
		.Having("MAX(Test.CommitDate)")
		.OrderBy("Task.Id")
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
			errMessage = "The results of " + student.lastName + " " + student.initials + " testing do not exist. The testing might not have been done.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(utility::conversions::to_string_t(answer));
	return result;
}