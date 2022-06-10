#include "ChatBot/Database.h"
#include "ChatbotConfig.h"
#include <iostream>

int main()
{
	BuilderSQL sql;
	Database db;
	if (!db.Open(DATABASE_PATH))
	{
		std::cout << db.ErrorMessage();
		return 1;
	}
	auto [success, answer] = db.Execute(
		sql.Begin().Terminate()
		.CreateTable("Task")
		(
			"Id INT PRIMARY KEY NOT NULL,"
			"Description TEXT NOT NULL"
			)
		.Terminate()
		.CreateTable("Variant")
		(
			"Id INTEGER PRIMARY KEY,"
			"TaskId INT NOT NULL,"
			"VariantId INT NOT NULL,"
			"Description TEXT NOT NULL"
			)
		.Terminate()
		.CreateTable("Groups")
		(
			"Id INTEGER PRIMARY KEY,"
			"Name TEXT NOT NULL UNIQUE"
			)
		.Terminate()
		.CreateTable("Student")
		(
			"Id INTEGER PRIMARY KEY,"
			"LName TEXT NOT NULL,"
			"Initials TEXT NOT NULL,"
			"GroupId INT"
			)
		.Terminate()
		.CreateTable("Test")
		(
			"Id INTEGER PRIMARY KEY,"
			"StudentId INT NOT NULL,"
			"TaskId INT NOT NULL,"
			"CommitDate TEXT NOT NULL,"
			"Status INT NOT NULL,"
			"Commentary TEXT,"
			"GitURL TEXT"
			)
		.Terminate()
		.Commit()
		.Terminate()
		.Build());

	if (!success)
	{
		std::cout << db.ErrorMessage();
		return 1;
	}
	return 0;
}