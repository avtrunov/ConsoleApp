#include "Chatbot\CmdShowResultsByTask.h"

json::value CmdShowResultsByTask::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Student.LName, Student.Initials, Groups.Name AS GroupName,"
			"Variant.VariantId, Variant.Description,"
			"Test.Status, Test.Commentary, MAX(Test.CommitDate) as Date, Test.GitURL")
		.From("Test")
		.Join("Variant").On("Variant.Id = Test.TaskId")
		.Join("Student").On("Student.Id = Test.StudentId")
		.Join("Groups").On("Groups.Id = Student.GroupId")
		.Where("Test.TaskId")
		.In(BuilderSQL{}.Select("Id")
			.From("Variant")
			.Where("TaskId = " + std::to_string(taskNum))
			.Build())
		.GroupBy("StudentId")
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
			errMessage = "The result of the task " + std::to_string(taskNum) + " testing does not exist. The testing might not have been done.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}