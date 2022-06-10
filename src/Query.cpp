#include "Chatbot\Query.h"

std::string Query::attributes = "";
std::string Query::result = "";

int Query::Callback(void* db, int AttributeNum, char** Value, char** AttributeName)
{
	attributes.clear();
	for (int i = 0; i < AttributeNum; i++)
	{
		attributes += std::string(AttributeName[i]) + ",";
	}
	attributes[attributes.size() - 1] = '\n';
	for (int i = 0; i < AttributeNum; i++)
	{
		result += Value[i] ? std::string(Value[i]) + "," : "NULL,";
	}
	result[result.size() - 1] = '\n';
	return 0;
}

std::pair<bool, std::string> Query::Execute(sqlite3* db, std::string&& sql)
{
	std::lock_guard<std::mutex> lock(mtx);
	result.clear();
	attributes.clear();
	char* errMsg = nullptr;
	if (sqlite3_exec(db, sql.c_str(), Callback, nullptr, &errMsg))
	{
		errMessage += "Failed to execute SQL: " + std::string(errMsg);
		sqlite3_free(errMsg);
		return { false,std::string() };
	}
	return { true, attributes + result };
}

std::string Query::ErrorMessage() const noexcept
{
	return errMessage;
}