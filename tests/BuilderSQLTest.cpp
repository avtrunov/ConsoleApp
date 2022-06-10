#include <gtest/gtest.h>
#include "Chatbot/BuilderSQL.h"


TEST(BuilderSQLTest, CreateTable)
{
	BuilderSQL sql;
	auto result = sql.CreateTable("Company")(
		"Id INT PRIMARY KEY NOT NULL,"
		"Name TEXT NOT NULL").Terminate()
		.Build();
	EXPECT_EQ(result, "CREATE TABLE IF NOT EXISTS Company (Id INT PRIMARY KEY NOT NULL,Name TEXT NOT NULL) ;");
}

TEST(BuilderSQLTest, InsertValues)
{
	BuilderSQL sql;
	auto result = sql.InsertInto("Company").Values("1, 'Paul', 32, 'California', 20000.00").Terminate().Build()
		+ sql.InsertInto("Company").Values("2, 'Allen', 25, 'Texas', 15000.00").Terminate().Build()
		+ sql.InsertInto("Company").Values("3, 'Teddy', 23, 'Norway', 20000.00").Terminate().Build();
	EXPECT_EQ(result, 
		"INSERT INTO Company VALUES(1, 'Paul', 32, 'California', 20000.00) ;" 
		"INSERT INTO Company VALUES(2, 'Allen', 25, 'Texas', 15000.00) ;"     
		"INSERT INTO Company VALUES(3, 'Teddy', 23, 'Norway', 20000.00) ;");
}

TEST(BuilderSQLTest, Select)
{
	BuilderSQL sql;
	auto result = sql.Select({ "1" }).Terminate().Build();
	EXPECT_EQ(result, "SELECT 1;");
	
	result = sql.Select({ "*" }).From("COMPANY").Where("SALARY >= 20000").GroupBy("ID").Terminate().Build();
	EXPECT_EQ(result, "SELECT * FROM COMPANY WHERE SALARY >= 20000 GROUP BY ID;");
}

TEST(BuilderSQLTest, Update)
{
	BuilderSQL sql;
	auto result = sql.Update("COMPANY").Set("SALARY = 25000").Where("ID = 7").Terminate().Build();
	EXPECT_EQ(result, "UPDATE COMPANY SET SALARY = 25000 WHERE ID = 7;");
}

TEST(BuilderSQLTest, Delete)
{
	BuilderSQL sql;
	auto result = sql.Delete().From("COMPANY").Where("ID = 7").Terminate().Build();
	EXPECT_EQ(result, "DELETE  FROM COMPANY WHERE ID = 7;");
}

TEST(BuilderSQLTest, SubQuery)
{
	BuilderSQL sql;
	auto result = sql.Delete().From("COMPANY").Where("AGE").In(
		BuilderSQL{}.Select({ "AGE" }).From("COMPANY").Where("AGE > 27").Build())
		.Terminate().Build();
	EXPECT_EQ(result, "DELETE  FROM COMPANY WHERE AGE IN(SELECT AGE FROM COMPANY WHERE AGE > 27) ;");
}