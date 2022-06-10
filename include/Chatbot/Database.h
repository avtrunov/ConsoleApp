#pragma once
#include "Chatbot/Query.h"
#include "Chatbot/BuilderSQL.h"

class Database
{
private:
	sqlite3* database = nullptr;
	std::string errMessage = "";
public:
	Database() = default;
	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;
	~Database();

	bool Open(const std::string& name);
	bool Close() noexcept;
	std::pair<bool,std::string> Execute(std::string&& sql);
	std::string ErrorMessage() const noexcept;
};