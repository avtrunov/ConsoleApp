#include "gtest/gtest.h"
#include "Chatbot/Database.h"

TEST(DatabaseTest, Open)
{
	Database db;
	EXPECT_TRUE(db.Open(":memory:"));
	EXPECT_FALSE(db.Open("badAttempt.db"));
}

TEST(DatabaseTest, Close)
{
	Database db;
	EXPECT_TRUE(db.Open(":memory:"));
	EXPECT_TRUE(db.Close());
	EXPECT_TRUE(db.Open(":memory:"));
}

class DatabaseTestF : public ::testing::Test
{
protected:
	void SetUp() override
	{
		db.Open(":memory:");
	}
	Database db;
	std::string TestTable = "TestTable";
};

TEST_F(DatabaseTestF, Execute)
{
	BuilderSQL sql;
	auto [status, answer] = db.Execute(
		sql.CreateTable(TestTable)
		("Id INT PRIMARY KEY NOT NULL, Sign TEXT NOT NULL").Terminate()
		.InsertInto("TestTable").Values("1, 'A'").Terminate()
		.InsertInto("TestTable").Values("2, 'B'").Terminate()
		.InsertInto("TestTable").Values("3, 'C'").Build()
	);
	EXPECT_TRUE(status);
	std::tie(status, answer) = db.Execute(
		sql.Select("*").From(TestTable).Where("Id = 1").Build()
	);
	EXPECT_TRUE(status);
	EXPECT_EQ(answer, "Id,Sign\n1,A\n");
}

TEST_F(DatabaseTestF, Error)
{
	BuilderSQL sql;
	auto [status, answer] = db.Execute(
		sql.Select("Sweater").From("Sweatshop").Build()
	);
	EXPECT_FALSE(status);
	EXPECT_EQ(answer, "");
	auto error = db.ErrorMessage();
	EXPECT_EQ("Failed to execute SQL: no such table: Sweatshop", db.ErrorMessage());
}