#pragma once
#include "Chatbot/Database.h"
#include "Chatbot/TableData.h"
#include <cpprest/json.h>

using namespace web;
using namespace utility::conversions;

class CommandSQL
{
protected:
	std::string errMessage = "";
public:
	CommandSQL() = default;
	CommandSQL(const CommandSQL&) = delete;
	CommandSQL& operator=(const CommandSQL&) = delete;
	virtual ~CommandSQL() = default;

	virtual json::value Execute(Database& db) = 0;
	virtual std::string ErrorMessage() const noexcept;
};

/*
												-General ER-model of the database-

-----------------------------																		  -----------------------------
|          Task             |																		  |			Groups			  |
-----------------------------																		  -----------------------------
|Id - INT PK NOT NULL       |																		  |Id - INT PK NOT NULL		  |
|Description - TEXT NOT NULL|																		  |Name - TEXT NOT NULL		  |
-----------------------------																	      -----------------------------
			|																									   |
			|																									   |
		   /|\																									  /|\
-----------------------------						-----------------------------					  -----------------------------
|		Variant				|						|			Test			|					  |			Student			  |
-----------------------------						-----------------------------					  -----------------------------
|Id - INT PK NOT NULL		|					/	|Id - INT PK NOT NULL       | \					  |Id - INT PK NOT NULL		  |
|TaskId - INT NOT NULL		|------------------<-	|TaskId - INT NOT NULL		| ->------------------|Name - TEXT NOT NULL		  |
|Variant - INT NOT NULL		|					\	|StudentID - INT NOT NULL	| /					  |Initials - TEXT NOT NULL	  |
|Description - TEXT NOT NULL|						|Status - INT NOT NULL		|					  |GroupId - INT NOT NULL	  |
-----------------------------						|Commentary - TEXT			|                     |Git - TEXT NOT NULL		  |
													|CommitDate - TEXT NOT NULL	|					  -----------------------------
													-----------------------------

*/