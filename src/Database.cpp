#include "Chatbot\Database.h"

bool Database::Open(const std::string& name)
{
	if (database != nullptr)
	{
		errMessage += "Database is already opened.";
		return false;
	}
	if (sqlite3_open(name.c_str(), &database))
	{
		errMessage += "Cannot open database: " + std::string(sqlite3_errmsg(database));
		return false;
	}
	return true;
}

bool Database::Close() noexcept
{
	if (sqlite3_close(database))
	{
		errMessage += "Cannot close database: " + std::string(sqlite3_errmsg(database));
		return false;
	}
	database = nullptr;
	return true;
}

Database::~Database()
{
	if (database != nullptr)
	{
		sqlite3_close(database);
	}
}

std::pair<bool,std::string> Database::Execute(std::string&& sql)
{
	Query q;
	auto [success, response] = q.Execute(database, std::move(sql));
	if (!success)
	{
		errMessage += q.ErrorMessage();
		return { false,std::string() };
	}
	return { true,response };
}

std::string Database::ErrorMessage() const noexcept
{
	return errMessage;
}