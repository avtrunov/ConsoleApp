#include "Chatbot\CmdShowResultByStudentTask.h"

json::value CmdShowResultByStudentTask::Execute(Database& database)
{
	BuilderSQL sql;
	auto [success, answer] = database.Execute(
		sql.Select("Student.LName, Student.Initials,"
			"Groups.Name AS GroupName,"
			"Variant.TaskId, Variant.VariantId, Variant.Description,"
			"Test.Status, Test.Commentary, MAX(Test.CommitDate) AS Date, Test.GitURL")
		.From("Test")
		.Join("Variant").On("Variant.Id = Test.TaskId")
		.Join("Student").On("Student.Id = Test.StudentId")
		.Join("Groups").On("Groups.Id = Student.GroupID")
		.Where("Student.LName LIKE '" + student.lastName + "' AND "
			"Student.Initials LIKE '" + student.initials + "' AND "
			"Variant.TaskId = " + std::to_string(taskNum))
		.GroupBy("Student.Id")
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
			errMessage += "The results of " + student.lastName + " " + student.initials
				+ " testing of the task " + std::to_string(taskNum) + " do not exist. The testing might not have been done.\n";
			return json::value::null();
		}
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("text"));
	result[U("data")] = json::value(to_string_t(answer));
	return result;
}