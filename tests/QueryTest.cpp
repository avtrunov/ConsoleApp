#include <gtest/gtest.h>
#include "Chatbot/Query.h"
#include "Chatbot/BuilderSQL.h"

TEST(QueryTest, Select1)
{
	sqlite3* db = nullptr;
	Query q;
	BuilderSQL sql;
	sqlite3_open(":memory:", &db);
	auto [success, responce] = q.Execute(db, sql.Select("1").Build());
	EXPECT_TRUE(success);
	EXPECT_EQ(responce[0], '1');

	sqlite3_close(db);
}

TEST(QueryTest, CreateTable)
{
	sqlite3* db = nullptr;
	Query q;
	BuilderSQL sql;
	sqlite3_open(":memory:", &db);

	auto [success, responce] = q.Execute(db,
		sql.CreateTable("TestTable")
		("Id INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL").Build());
	EXPECT_TRUE(success);

	sqlite3_close(db);
}

TEST(QueryTest, InsertInto)
{
	sqlite3* db = nullptr;
	Query q;
	BuilderSQL sql;
	sqlite3_open(":memory:", &db);

	auto [success, responce] = q.Execute(db,
		sql.CreateTable("TestTable")
		("Id INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL").Terminate()
		.InsertInto("TestTable").Values("1, 'A'").Terminate()
		.InsertInto("TestTable").Values("2, 'B'").Terminate()
		.InsertInto("TestTable").Values("3, 'C'").Terminate()
		.Build());
	EXPECT_TRUE(success);

	sqlite3_close(db);
}

class QueryTestF : public ::testing::Test
{
protected:
	void SetUp() override
	{
		Query q;
		BuilderSQL sql;
		sqlite3_open(":memory:", &db);
		q.Execute(db,
		sql.CreateTable(TestTable)
			("Id INT PRIMARY KEY NOT NULL, Sign TEXT NOT NULL").Terminate()
			.InsertInto("TestTable").Values("1, 'A'").Terminate()
			.InsertInto("TestTable").Values("2, 'B'").Terminate()
			.InsertInto("TestTable").Values("3, 'C'").Terminate()
			.Build());
	}
	void TearDown() override
	{
		sqlite3_close(db);
	}
	sqlite3* db = nullptr;
	std::string TestTable = "TestTable";
};

TEST_F(QueryTestF, SelectFromTable)
{
	Query q;
	BuilderSQL sql;

	auto [success, answer] = q.Execute(db,
		sql.Select("*").From(TestTable).Where("Id = 2").Build());
	EXPECT_TRUE(success);
	EXPECT_EQ(answer, "Id,Sign\n2,B\n");
}

TEST_F(QueryTestF, UpdateTable)
{
	Query q;
	BuilderSQL sql;

	auto [success, answer] = q.Execute(db,
		sql.Update(TestTable).Set("Sign = 'Z'").Where("Id = 3").Terminate()
		.Select("*").From(TestTable).Where("Id = 3")
		.Build());
	EXPECT_TRUE(success);
	EXPECT_EQ(answer, "Id,Sign\n3,Z\n");
}

TEST_F(QueryTestF, DeleteFromTable)
{
	Query q;
	BuilderSQL sql;

	auto [success, answer] = q.Execute(db,
		sql.Delete().From(TestTable).Where("Id").In("2,3").Terminate()
		.Select("*").From(TestTable)
		.Build());
	EXPECT_TRUE(success);
	EXPECT_EQ(answer, "Id,Sign\n1,A\n");
}

TEST_F(QueryTestF, JoinTables)
{
	Query q;
	BuilderSQL sql;

	auto [success, answer] = q.Execute(db,
		sql.CreateTable("JoinTable")
		("Id INT PRIMARY KEY NOT NULL, Name TEXT NOT NULL").Terminate()
		.InsertInto("JoinTable").Values("1, 'Apple'").Terminate()
		.InsertInto("JoinTable").Values("2, 'Beet'").Terminate()
		.InsertInto("JoinTable").Values("3, 'Cucumber'")
		.Build());
	EXPECT_TRUE(success);
	EXPECT_EQ(answer, "");

	std::tie(success, answer) = q.Execute(db,
		sql.Select("Sign, JoinTable.Name").From(TestTable)
		.Join("JoinTable").On("TestTable.Id = JoinTable.Id")
		.Where("TestTable.Id = 2")
		.Build());
	EXPECT_TRUE(success);
	EXPECT_EQ(answer, "Sign,Name\nB,Beet\n");
}