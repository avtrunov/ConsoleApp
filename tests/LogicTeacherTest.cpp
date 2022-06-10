#include <gtest/gtest.h>
#include "Chatbot/Logic.h"

class LogicTeacherTest : public ::testing::Test
{
protected:
	Logic<Teacher> base;
};

TEST_F(LogicTeacherTest, AddTask)
{
	std::string msg = "add task 1 \"Implement sorting algorithm\"";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The task 1 has been added to the database.\n");

	msg = "add task 2 \"Implement linkd list\"";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The task 2 has been added to the database.\n");
}

TEST_F(LogicTeacherTest, ChangeTask)
{
	std::string msg = "change task 2 \"Implement linked list\"";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The task 2 description has been changed.\n");
}

TEST_F(LogicTeacherTest, ShowTask)
{
	std::string msg = "show task 1";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(), L"Id,Description\n1,Implement sorting algorithm\n");

	msg = "show task 20";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The task 20 does not exist.\n");

	msg = "show task -2";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"Parsing error: ");
	/*
		msg = L"отобразить заданье 2";
		EXPECT_FALSE(base.Process(msg));
		EXPECT_EQ(base.GetErrorMessage(), L"Не получилось распознать сообщение. Ошибка в слове: \"заданье\". Возможно вы имели ввиду:\nвариант\nвсе\nзадание\n");

		msg = L"отобразить ";
		EXPECT_FALSE(base.Process(msg));
		EXPECT_EQ(base.GetErrorMessage(), L"Не получилось распознать сообщение. Слишком короткое сообщение. Попробуйте добавить:\nвариант\nвсе\nзадание\n");
	*/
	msg = "show task 20000000000000000";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"Parsing error: Argument out of range.\n");
}

TEST_F(LogicTeacherTest, AddVariant)
{
	std::string msg = "add task 1 variant 1 \"Bubble sort\"";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant 1 of the task 1 has been added to the database.\n");

	msg = "add task 1 variant 2 \"Radix sort\"";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant 2 of the task 1 has been added to the database.\n");

	msg = "add task 1 variant 3 \"Heap sort\"";
	responce = base.Process(msg); 
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant 3 of the task 1 has been added to the database.\n");
}

TEST_F(LogicTeacherTest, ChangeVariant)
{
	std::string msg = "change task 1 variant 1 \"Quick sort\"";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant 1 description of the task 1 has been changed.\n");
}

TEST_F(LogicTeacherTest, ShowVariant)
{
	std::string msg = "show task 1 variant 1";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(), L"Id,Description\n1,Quick sort\n");

	msg = "show task 4 variant 2";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant 2 of the task 4 does not exist.\n");
}

TEST_F(LogicTeacherTest, ShowAllTasks)
{
	std::string msg = "show all tasks";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(), L"Id,Description\n1,Implement sorting algorithm\n2,Implement linked list\n");
}

TEST_F(LogicTeacherTest, ShowAllVariants)
{
	std::string msg = "show all variants";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(),
		L"TaskId,Description,VariantId,Description\n"
		L"1,Implement sorting algorithm,1,Quick sort\n"
		L"1,Implement sorting algorithm,2,Radix sort\n"
		L"1,Implement sorting algorithm,3,Heap sort\n");
}

TEST_F(LogicTeacherTest, DeleteVariant)
{
	std::string msg = "delete task 1 variant 3";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant 3 of the task 1 has been deleted.\n");
}

TEST_F(LogicTeacherTest, ShowVariantByTask)
{
	std::string msg = "show task 1 variant all";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(), L"Id,Description\n1,Quick sort\n2,Radix sort\n");

	msg = "show task 10 variant all";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The variant list is empty.\n");
}

TEST_F(LogicTeacherTest, DeleteTask)
{
	std::string msg = "delete task 1";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The task 1 has been deleted.\n");

	msg = "delete task 2";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The task 2 has been deleted.\n");
}

TEST_F(LogicTeacherTest, AddGroup)
{
	std::string msg = "add group 404";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The group 404 has been added to the database.\n");

	msg = "add group 404";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"This group already exists.\n");
	
	msg = "add group 402";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The group 402 has been added to the database.\n");
}

TEST_F(LogicTeacherTest, ChangeGroup)
{
	std::string msg = "change group 1 name to 405";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The group name has been changed.\n");
}

TEST_F(LogicTeacherTest, ShowGroups)
{
	std::string msg = "show all groups";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(), L"Id,Name,StudentCount\n2,402,0\n1,405,0\n");
}

TEST_F(LogicTeacherTest, AddStudent)
{
	std::string msg = "add student Ianov II";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The student Ianov II has been added to the database.\n");

	msg = "add student Petrov P 405";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The student Petrov P has been added to the database.\n");
}

TEST_F(LogicTeacherTest, ChangeStudentParams)
{
	std::string msg = "change student 1 last name to Ivanov";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The student's last name has been changed.\n");

	msg = "change student 2 initials to PP";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The student's initials has been changed.\n");

	msg = "change student 1 group to 402";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The student's group name has been changed.\n");
}

TEST_F(LogicTeacherTest, ShowAllStudents)
{
	std::string msg = "show all students";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(),
		L"Id,LName,Initials,GroupName\n"
		L"2,Petrov,PP,405\n"
		L"1,Ivanov,II,402\n");
}

TEST_F(LogicTeacherTest, ShowStudentsFromGroup)
{
	std::string msg = "show students from group 405";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"table");
	EXPECT_EQ(responce[U("data")].as_string(),
		L"Id,LName,Initials,GroupName\n"
		L"2,Petrov,PP,405\n");
}

TEST_F(LogicTeacherTest, DeleteStudent)
{
	std::string msg = "delete student 1";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The student has been deleted from the database.\n");
}

TEST_F(LogicTeacherTest, DeleteStudentsFromGroup)
{
	std::string msg = "delete students from group 405";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The students of the group 405 has been deleted.\n");
}

TEST_F(LogicTeacherTest, DeleteGroup)
{
	std::string msg = "delete group 405";
	json::value responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The group 405 has been deleted from the database.\n");

	msg = "delete group 402";
	responce = base.Process(msg);
	EXPECT_EQ(responce[U("type")].as_string(), L"text");
	EXPECT_EQ(responce[U("data")].as_string(), L"The group 402 has been deleted from the database.\n");
}

/*
TEST_F(LogicTeacherTest, ShowAllResults)
{
	std::string msg = L"результаты по всем заданиям";
	EXPECT_TRUE(base.Process(msg));
	EXPECT_EQ(base.GetResult(),
		L"LName,Initials,GroupName,TaskId,VariantId,Description,Status,Commentary,Date,GitURL\n"
		L"Perov,VA,107M,1,3,Radix Sort,0,Test 4 failed,2021-12-29 13:06:51,git\n"
		L"Perov,VA,107M,2,1,Single linked list,0,Test 5 failed,2021-12-29 13:17:57,git\n"
		L"Spirin,SD,107M,1,1,Quick Sort,0,Test 2-4 failed,2021-12-29 13:07:10,git\n"
		L"Spirin,SD,107M,2,2,Double linked list,0,Test 4 failed,2021-12-29 13:18:13,git\n"
		L"Spirin,SD,107M,3,1,Red-black tree,0,Test 3 failed,2021-12-29 13:19:05,git\n"
		L"Kuzmin,DU,104M,1,2,Heap Sort,1,Success,2021-12-29 13:06:23,git\n"
		L"Kuzmin,DU,104M,2,2,Double linked list,1,Success,2021-12-29 13:17:30,git\n"
		L"Trunov,AV,104M,1,1,Quick Sort,1,Success,2021-12-29 13:06:07,git\n"
		L"Trunov,AV,104M,3,1,Red-black tree,0,No tests were made,2021-12-29 13:18:51,git\n"
		L"Trunov,AV,104M,2,1,Single linked list,0,Test 2 failed,2021-12-29 13:17:06,git\n");
}

TEST_F(LogicTeacherTest, ShowResultsByTask)
{
	std::string msg = L" результаты  по заданию 3";
	EXPECT_TRUE(base.Process(msg));
	EXPECT_EQ(base.GetResult(),
		L"LName,Initials,GroupName,VariantId,Description,Status,Commentary,Date,GitURL\n"
		L"Spirin,SD,107M,1,Red-black tree,0,Test 3 failed,2021-12-29 13:19:05,git\n"
		L"Trunov,AV,104M,1,Red-black tree,0,No tests were made,2021-12-29 13:18:51,git\n");

	msg = L" результаты  по заданию 10";
	EXPECT_FALSE(base.Process(msg));
	EXPECT_EQ(base.GetErrorMessage(), L"Результаты проверки по заданию 10 отсутствуют.\n");
}

TEST_F(LogicTeacherTest, ShowResultsByStudent)
{
	std::string msg = L" результаты  студента kuzmin du";
	EXPECT_TRUE(base.Process(msg));
	EXPECT_EQ(base.GetResult(),
		L"TaskId,Description,VariantId,Description,Status,Commentary,CommitDate,GitURL\n"
		L"1,Implement sorting algorithm,2,Heap Sort,1,Success,2021-12-29 13:06:23,git\n"
		L"2,Implement linked list,2,Double linked list,1,Success,2021-12-29 13:17:30,git\n");

	msg = L" результаты  студента сосов сс";
	EXPECT_FALSE(base.Process(msg));
	EXPECT_EQ(base.GetErrorMessage(), L"Результаты проверки студента сосов сс отсутствуют.\n");
}

TEST_F(LogicTeacherTest, ShowResultsByStudentTask)
{
	std::string msg = L" результаты  студента trunov av по заданию 1";
	EXPECT_TRUE(base.Process(msg));
	EXPECT_EQ(base.GetResult(),
		L"LName,Initials,GroupName,TaskId,VariantId,Description,Status,Commentary,Date,GitURL\n"
		L"Trunov,AV,104M,1,1,Quick Sort,1,Success,2021-12-29 13:06:07,git\n");

	msg = L" результаты  студента сосов ав по заданию 1";
	EXPECT_FALSE(base.Process(msg));
	EXPECT_EQ(base.GetErrorMessage(), L"Результат проверки студента сосов ав по заданию 1 отсутствует.\n");
}
*/