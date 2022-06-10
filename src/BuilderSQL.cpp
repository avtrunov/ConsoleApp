#include "Chatbot\BuilderSQL.h"

BuilderSQL& BuilderSQL::LeftJoin(const std::string& str)
{
	sql += " LEFT JOIN " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Begin()
{
	sql += "BEGIN";
	return *this;
}

BuilderSQL& BuilderSQL::Commit()
{
	sql += "COMMIT";
	return *this;
}

BuilderSQL& BuilderSQL::CreateTable(const std::string& str)
{
	sql += "CREATE TABLE IF NOT EXISTS " + str;
	return *this;
}

BuilderSQL& BuilderSQL::DropTable(const std::string& str)
{
	sql += "DROP TABLE " + str;
	return *this;
}

BuilderSQL& BuilderSQL::InsertInto(const std::string& str)
{
	sql += "INSERT INTO " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Values(const std::string& str)
{
	sql += " VALUES(" + str + ") ";
	return *this;
}

BuilderSQL& BuilderSQL::Update(const std::string& str)
{
	sql += "UPDATE " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Set(const std::string& str)
{
	sql += " SET " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Select(const std::string& str)
{
	sql += "SELECT " + str;
	return *this;
}

BuilderSQL& BuilderSQL::From(const std::string& str)
{
	sql += " FROM " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Delete(const std::string& str)
{
	sql += "DELETE " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Where(const std::string& str)
{
	sql += " WHERE " + str;
	return *this;
}

BuilderSQL& BuilderSQL::OrderBy(const std::string& str)
{
	sql += " ORDER BY " + str;
	return *this;
}

BuilderSQL& BuilderSQL::GroupBy(const std::string& str)
{
	sql += " GROUP BY " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Having(const std::string& str)
{
	sql += " HAVING " + str;
	return *this;
}

BuilderSQL& BuilderSQL::In(const std::string& str)
{
	sql += " IN(" + str + ") ";
	return *this;
}

BuilderSQL& BuilderSQL::Join(const std::string& str)
{
	sql += " JOIN " + str;
	return *this;
}

BuilderSQL& BuilderSQL::On(const std::string& str)
{
	sql += " ON " + str;
	return *this;
}

BuilderSQL& BuilderSQL::Distinct(const std::string& str)
{
	sql += " DISTINCT " + str;
	return *this;
}

BuilderSQL& BuilderSQL::operator()(const std::string& str)
{
	sql += " (" + str + ") ";
	return *this;
}

BuilderSQL& BuilderSQL::Terminate()
{
	sql += ";";
	return *this;
}

std::string BuilderSQL::Build()
{
	return std::move(sql);
}