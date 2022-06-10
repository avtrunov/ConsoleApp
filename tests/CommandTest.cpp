#include <gtest/gtest.h>
#include "Chatbot/CommandHeaderList.h"
#include "Chatbot/TableData.h"
#include "ChatbotConfig.h"

class CommandTest : public ::testing::Test
{
protected:
	Database db;
	void SetUp() override
	{
		db.Open(DATABASE_PATH);
	}
};

TEST_F(CommandTest, AddTask)
{
	CmdAddTask cmd({ 1,"Implement sorting algoritm" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The task 1 has been added to the database.\n");

	CmdAddTask cmd1({ 1,"Implement sorting algoritm" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer, json::value::null());
	EXPECT_EQ(cmd1.ErrorMessage(), "This task already exists.\n");

	CmdAddTask cmd2({ 2,"Implement linked list" });
	answer = cmd2.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The task 2 has been added to the database.\n");
}

TEST_F(CommandTest, ChangeTask)
{
	CmdChangeTask cmd({ 1,"Implement sorting algorithm" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The task 1 description has been changed.\n");
}

TEST_F(CommandTest, ShowTask)
{
	CmdShowTask cmd1({ 1,"" });
	json::value answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(), L"Id,Description\n1,Implement sorting algorithm\n");

	CmdShowTask cmd2({ 0,"" });
	answer = cmd2.Execute(db);
	EXPECT_EQ(answer, json::value::null());
	EXPECT_EQ(cmd2.ErrorMessage(), "The task 0 does not exist.\n");
}

TEST_F(CommandTest, AddVariant)
{
	CmdAddVariant cmd(Table::Task{ 1,"" }, Table::Variant{ 1, "Bubble sort" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The variant 1 of the task 1 has been added to the database.\n");

	CmdAddVariant cmd1(Table::Task{ 1,"" }, Table::Variant{ 2, "Radix sort" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The variant 2 of the task 1 has been added to the database.\n");

	CmdAddVariant cmd2(Table::Task{ 1,"" }, Table::Variant{ 3, "Heap sort" });
	answer = cmd2.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The variant 3 of the task 1 has been added to the database.\n");
}

TEST_F(CommandTest, ChangeVariant)
{
	CmdChangeVariant cmd(Table::Task{ 1,"" }, Table::Variant{ 1, "Quick sort" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The variant 1 description of the task 1 has been changed.\n");
}

TEST_F(CommandTest, ShowVariant)
{
	CmdShowVariant cmd(Table::Task{ 1,"" }, Table::Variant{ 3,"" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(), L"Id,Description\n3,Heap sort\n");

	CmdShowVariant cmd1(Table::Task{ 10,"" }, Table::Variant{ 20,"" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer, json::value::null());
	EXPECT_EQ(cmd1.ErrorMessage(), "The variant 20 of the task 10 does not exist.\n");
}

TEST_F(CommandTest, ShowAllTasks)
{
	CmdShowAllTasks cmd1;
	json::value answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(),
		L"Id,Description\n"
		L"1,Implement sorting algorithm\n"
		L"2,Implement linked list\n");

	Database empty;
	empty.Open(":memory:");
	empty.Execute(BuilderSQL{}.CreateTable("Task")("ID INT PRIMARY KEY, RR TEXT").Build());
	CmdShowAllTasks cmd3;
	answer = cmd3.Execute(empty);
	EXPECT_EQ(answer, json::value::null());
	EXPECT_EQ(cmd3.ErrorMessage(), "The task list is empty.\n");
}

TEST_F(CommandTest, ShowAllVariants)
{
	CmdShowAllVariants cmd;
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(),
		L"TaskId,Description,VariantId,Description\n"
		L"1,Implement sorting algorithm,1,Quick sort\n"
		L"1,Implement sorting algorithm,2,Radix sort\n"
		L"1,Implement sorting algorithm,3,Heap sort\n");
}

TEST_F(CommandTest, DeleteVariant)
{
	CmdDeleteVariant cmd(Table::Task{ 1,"" }, Table::Variant{ 3, "" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The variant 3 of the task 1 has been deleted.\n");
}

TEST_F(CommandTest, ShowVariantsByTask)
{
	CmdShowVariantsByTask cmd(Table::Task{ 1,"" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(), L"Id,Description\n1,Quick sort\n2,Radix sort\n");

	CmdShowVariantsByTask cmd1(Table::Task{ 10,"" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer, json::value::null());
	EXPECT_EQ(cmd1.ErrorMessage(), "The variant list is empty.\n");
}

TEST_F(CommandTest, DeleteTask)
{
	CmdDeleteTask cmd({ 1,"" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The task 1 has been deleted.\n");

	CmdDeleteTask cmd1({ 2,"" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The task 2 has been deleted.\n");
}

TEST_F(CommandTest, AddGroup)
{
	CmdAddGroup cmd( Table::Group{ 0,"404B" });
	json::value	answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The group 404B has been added to the database.\n");

	CmdAddGroup cmd1( Table::Group{ 0,"404B" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer, json::value::null());
	EXPECT_EQ(cmd1.ErrorMessage(), "This group already exists.\n");

	CmdAddGroup cmd2(Table::Group{ 0,"402B" });
	answer = cmd2.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The group 402B has been added to the database.\n");
}

TEST_F(CommandTest, ChangeGroup)
{
	CmdChangeGroup cmd( Table::Group{ 1,"405B" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The group name has been changed.\n");
}

TEST_F(CommandTest, ShowGroups)
{
	CmdShowGroups cmd;
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(), L"Id,Name,StudentCount\n2,402B,0\n1,405B,0\n");
}

TEST_F(CommandTest, AddStudent)
{
	CmdAddStudent cmd( Table::Group{ 0,"" }, Table::Student{ 0,"Ivanov","II" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The student Ivanov II has been added to the database.\n");
	
	CmdAddStudent cmd1( Table::Group{ 0,"405B" }, Table::Student{ 0,"Petrov","PP" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The student Petrov PP has been added to the database.\n");
}

TEST_F(CommandTest, ChangeStudentParams)
{
	CmdChangeStudentName cmd( Table::Student{ 1,"Vanov","" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The student's last name has been changed.\n");

	CmdChangeStudentInitials cmd1( Table::Student{ 1,"","VV" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The student's initials has been changed.\n");

	CmdChangeStudentGroup cmd2( Table::Student{ 1,"","" }, Table::Group{ 0,"402B" });
	answer = cmd2.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The student's group name has been changed.\n");
}

TEST_F(CommandTest, ShowAllStudents)
{
	CmdShowAllStudents cmd;
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(),
		L"Id,LName,Initials,GroupName\n"
		L"2,Petrov,PP,405B\n"
		L"1,Vanov,VV,402B\n");
}

TEST_F(CommandTest, ShowStudentsFromGroup)
{
	CmdShowStudentsFromGroup cmd(Table::Group{ 0,"402B" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"table");
	EXPECT_EQ(answer[U("data")].as_string(),
		L"Id,LName,Initials,GroupName\n"
		L"1,Vanov,VV,402B\n");
}

TEST_F(CommandTest, DeleteStudent)
{
	CmdDeleteStudent cmd( Table::Student{ 1,"","" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The student has been deleted from the database.\n");
}

TEST_F(CommandTest, DeleteStudentsFromGroup)
{
	CmdDeleteStudentsFromGroup cmd( Table::Group{0,"405B"});
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The students of the group 405B has been deleted.\n");
}


TEST_F(CommandTest, DeleteGroup)
{
	CmdDeleteGroup cmd( Table::Group{ 0,"405B" });
	json::value answer = cmd.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The group 405B has been deleted from the database.\n");

	CmdDeleteGroup cmd1(Table::Group{ 0,"402B" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer[U("type")].as_string(), L"text");
	EXPECT_EQ(answer[U("data")].as_string(), L"The group 402B has been deleted from the database.\n");
}
/*
TEST_F(CommandTest, ShowResultsByStudent)
{
	CmdShowResultsByStudent cmd1( Table::Student{ 0, "Kuzmin","DU" });
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer,
		"TaskId,Description,VariantId,Description,Status,Commentary,CommitDate,GitURL\n"
		"1,Implement sorting algorithm,2,Heap Sort,1,Success,2021-12-29 13:06:23,git\n"
		"2,Implement linked list,2,Double linked list,1,Success,2021-12-29 13:17:30,git\n");

	CmdShowResultsByStudent cmd2( Table::Student{ 0, "Иванов","ИИ" });
	answer = cmd2.Execute(db);
	EXPECT_FALSE(success);
	EXPECT_EQ(answer, "");
	EXPECT_EQ(cmd2.ErrorMessage(), "Результаты проверки студента Иванов ИИ отсутствуют.\n");
}

TEST_F(CommandTest, ShowAllResults)
{
	CmdShowAllResults cmd1;
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer,
		"LName,Initials,GroupName,TaskId,VariantId,Description,Status,Commentary,Date,GitURL\n"
		"Perov,VA,107M,1,3,Radix Sort,0,Test 4 failed,2021-12-29 13:06:51,git\n"
		"Perov,VA,107M,2,1,Single linked list,0,Test 5 failed,2021-12-29 13:17:57,git\n"
		"Spirin,SD,107M,1,1,Quick Sort,0,Test 2-4 failed,2021-12-29 13:07:10,git\n"
		"Spirin,SD,107M,2,2,Double linked list,0,Test 4 failed,2021-12-29 13:18:13,git\n"
		"Spirin,SD,107M,3,1,Red-black tree,0,Test 3 failed,2021-12-29 13:19:05,git\n"
		"Kuzmin,DU,104M,1,2,Heap Sort,1,Success,2021-12-29 13:06:23,git\n"
		"Kuzmin,DU,104M,2,2,Double linked list,1,Success,2021-12-29 13:17:30,git\n"
		"Trunov,AV,104M,1,1,Quick Sort,1,Success,2021-12-29 13:06:07,git\n"
		"Trunov,AV,104M,3,1,Red-black tree,0,No tests were made,2021-12-29 13:18:51,git\n"
		"Trunov,AV,104M,2,1,Single linked list,0,Test 2 failed,2021-12-29 13:17:06,git\n");
}

TEST_F(CommandTest, ShowResultsByTask)
{
	CmdShowResultsByTask cmd2( Table::Task{ 3,""});
	answer = cmd2.Execute(db);
	EXPECT_EQ(answer,
		"LName,Initials,GroupName,VariantId,Description,Status,Commentary,Date,GitURL\n"
		"Spirin,SD,107M,1,Red-black tree,0,Test 3 failed,2021-12-29 13:19:05,git\n"
		"Trunov,AV,104M,1,Red-black tree,0,No tests were made,2021-12-29 13:18:51,git\n");

	CmdShowResultsByTask cmd3( Table::Task{ 7,""});
	answer = cmd3.Execute(db);
	EXPECT_FALSE(success);
	EXPECT_EQ(answer, "");
	EXPECT_EQ(cmd3.ErrorMessage(), "Результаты проверки по заданию 7 отсутствуют.\n");
}

TEST_F(CommandTest, ShowResultByStudentTask)
{
	CmdShowResultByStudentTask cmd1( Table::Student{0, "Trunov","AV" }, Table::Task{ 1,""});
	answer = cmd1.Execute(db);
	EXPECT_EQ(answer,
		"LName,Initials,GroupName,TaskId,VariantId,Description,Status,Commentary,Date,GitURL\n"
		"Trunov,AV,104M,1,1,Quick Sort,1,Success,2021-12-29 13:06:07,git\n");

	CmdShowResultByStudentTask cmd2( Table::Student{0, "Random","Name" }, Table::Task{ 1,""});
	answer = cmd2.Execute(db);
	EXPECT_FALSE(success);
	EXPECT_EQ(answer, "");
	EXPECT_EQ(cmd2.ErrorMessage(), "Результат проверки студента Random Name по заданию 1 отсутствует.\n");
}
*/