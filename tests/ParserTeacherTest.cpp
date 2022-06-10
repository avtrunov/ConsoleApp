#include <gtest/gtest.h>
#include "Chatbot/ParserTeacher.h"


class ParserTeacherTest : public ::testing::Test
{
protected:
	ParserTeacher in;
};

TEST_F(ParserTeacherTest, AddTask)
{
	std::string test = "add task 1 \"Implement sorting\"";
	auto cmd= in.Parse(test);
	CmdAddTask* res;
	EXPECT_TRUE(res = dynamic_cast<CmdAddTask*>(cmd.get()));
}


TEST_F(ParserTeacherTest, ChangeTask)
{
	std::string test = "change task 2 \"list single-linked\"";
	auto cmd = in.Parse(test);
	CmdChangeTask* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, DeleteTask)
{
	std::string test = "delete task 3";
	auto cmd = in.Parse(test);
	CmdDeleteTask* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowTask)
{
	std::string test = "show task 4";
	auto cmd = in.Parse(test);
	CmdShowTask* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowAllTasks)
{
	std::string test = "show all tasks";
	auto cmd = in.Parse(test);
	CmdShowAllTasks* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, AddVariant)
{
	std::string test = "add task 4 variant 3 \"list\"";
	auto cmd = in.Parse(test);
	CmdAddVariant* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ChangeVariant)
{
	std::string test = "change task 1 variant 1 \"radix sort\"";
	auto cmd = in.Parse(test);
	CmdChangeVariant* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, DeleteVariant)
{
	std::string test = "delete task 2 variant 10";
	auto cmd = in.Parse(test);
	CmdDeleteVariant* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowVariant)
{
	std::string test = "show task 1 variant 12";
	auto cmd = in.Parse(test);
	CmdShowVariant* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowAllVariantsByTask)
{
	std::string test = "show task 15 variant all";
	auto cmd = in.Parse(test);
	CmdShowVariantsByTask* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowAllVariants)
{
	std::string test = "show all variants";
	auto cmd = in.Parse(test);
	CmdShowAllVariants* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, NumberOutOfRange)
{
	std::string test = "delete task 2 variant 100000000000";
	EXPECT_EQ(in.Parse(test),nullptr);
	EXPECT_EQ(in.ErrorMessage(), "Argument out of range.\n");
}

TEST_F(ParserTeacherTest, LetterInsteadOfNumber)
{
	std::string test = "delete task А variant В";
	EXPECT_EQ(in.Parse(test), nullptr);
}
TEST_F(ParserTeacherTest, ShortMessage)
{
	std::string test = "delete variant";
	EXPECT_EQ(in.Parse(test), nullptr);
}
TEST_F(ParserTeacherTest, StringWithPunctuation)
{
	std::string test = "add task 3 variant 4 \" l;i;s;t\"";
	EXPECT_EQ(in.Parse(test), nullptr);
}
/*
TEST_F(ParserTeacherTest, StringWithControlLetters)
{
	std::string test = "\n\n\nотобразить\n\t\nвсе  \t   варианты \t\t по  \t всем  \t \t заданиям";
	auto cmd = in.Parse(test);
	CmdShowAllVariants* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}*/

TEST_F(ParserTeacherTest, LongMessage)
{
	std::string test = "show all variants somedata";
	EXPECT_EQ(in.Parse(test), nullptr);
}

TEST_F(ParserTeacherTest, EmptyMessage)
{
	std::string test = "";
	EXPECT_EQ(in.Parse(test), nullptr);
}

TEST_F(ParserTeacherTest, AddGroup)
{
	std::string test = "add group 8О-404B";
	auto cmd = in.Parse(test);
	CmdAddGroup* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ChangeGroup)
{
	std::string test = "change group 1 name to 8О-107M";
	auto cmd = in.Parse(test);
	CmdChangeGroup* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, DeleteGroup)
{
	std::string test = "delete group 2";
	auto cmd = in.Parse(test);
	CmdDeleteGroup* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowGroups)
{
	std::string test = "show all groups";
	auto cmd = in.Parse(test);
	CmdShowGroups* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, AddStudent)
{
	std::string test = "add student trunov av 404B";
	auto cmd = in.Parse(test);
	CmdAddStudent* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));

	test = "add student trunov av";
	cmd = in.Parse(test);
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ChangeStudentName)
{
	std::string test = "change student 1 last name to trunov";
	auto cmd = in.Parse(test);
	CmdChangeStudentName* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ChangeStudentInitials)
{
	std::string test = "change student 1 initials to av";
	auto cmd = in.Parse(test);
	CmdChangeStudentInitials* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ChangeStudentGroup)
{
	std::string test = "change student 6 group to 107M";
	auto cmd = in.Parse(test);
	CmdChangeStudentGroup* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, DeleteStudent)
{
	std::string test = "delete student 34";
	auto cmd = in.Parse(test);
	CmdDeleteStudent* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, DeleteStudentsFromGroup)
{
	std::string test = "delete students from group 404";
	auto cmd = in.Parse(test);
	CmdDeleteStudentsFromGroup* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowStudentsFromGroup)
{
	std::string test = "show students from group 1-404";
	auto cmd = in.Parse(test);
	CmdShowStudentsFromGroup* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowAllStudents)
{
	std::string test = "show all students";
	auto cmd = in.Parse(test);
	CmdShowAllStudents* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowResultsByTask)
{
	std::string test = "results task 3";
	auto cmd = in.Parse(test);
	CmdShowResultsByTask* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowResultsByStudent)
{
	std::string test = "results student trunov av";
	auto cmd = in.Parse(test);
	CmdShowResultsByStudent* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowAllResults)
{
	std::string test = "results all tasks";
	auto cmd = in.Parse(test);
	CmdShowAllResults* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, ShowResultsByStudentTask)
{
	std::string test = "results student trunov av task 2";
	auto cmd = in.Parse(test);
	CmdShowResultByStudentTask* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}

TEST_F(ParserTeacherTest, GetCameraFrame)
{
	std::string test = "get camera frame";
	auto cmd = in.Parse(test);
	CmdGetCameraFrame* res;
	EXPECT_TRUE(res = dynamic_cast<decltype(res)>(cmd.get()));
}