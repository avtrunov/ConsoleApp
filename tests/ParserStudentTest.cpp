#include <gtest/gtest.h>
#include "Chatbot/ParserStudent.h"

class ParserStudentTest : public ::testing::Test
{
protected:
	ParserStudent in;
};

TEST_F(ParserStudentTest, ShowTask)
{
	std::string test = "show task 4";
	auto cmd = in.Parse(test);
	CmdShowTask* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowTask*>(cmd.get()));
}

TEST_F(ParserStudentTest, ShowAllTasks)
{
	std::string test = "show all tasks";
	auto cmd= in.Parse(test);
	CmdShowAllTasks* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowAllTasks*>(cmd.get()));
}

TEST_F(ParserStudentTest, ShowVariant)
{
	std::string test = "show task 5 variant 12";
	auto cmd = in.Parse(test);
	CmdShowVariant* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowVariant*>(cmd.get()));
}

TEST_F(ParserStudentTest, ShowAllVariantsByTask)
{
	std::string test = "show task 5 variant all";
	auto cmd = in.Parse(test);
	CmdShowVariantsByTask* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowVariantsByTask*>(cmd.get()));
}

TEST_F(ParserStudentTest, ShowAllVariants)
{
	std::string test = "show all variants";
	auto cmd = in.Parse(test);
	CmdShowAllVariants* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowAllVariants*>(cmd.get()));
}

TEST_F(ParserStudentTest, ShowStudentsByGroup)
{
	std::string test = "show students from group 1-404";
	auto cmd = in.Parse(test);
	CmdShowStudentsFromGroup* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowStudentsFromGroup*>(cmd.get()));
}

TEST_F(ParserStudentTest, ShowAllStudents)
{
	std::string test = "show all students";
	auto cmd = in.Parse(test);
	CmdShowAllStudents* res;
	EXPECT_TRUE(res = dynamic_cast<CmdShowAllStudents*>(cmd.get()));
}