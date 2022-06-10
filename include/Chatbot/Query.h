#pragma once
#include <string>
#include <sqlite3.h>
#include <mutex>

class Query
{
private:
	std::string errMessage = "";
	static std::string attributes;
	static std::string result;
	static int Callback(void* db, int AttributeNum, char** Value, char** AttributeName);
	std::mutex mtx;
public:
	std::pair<bool, std::string> Execute(sqlite3* db, std::string&& sql);
	std::string ErrorMessage() const noexcept;
};

