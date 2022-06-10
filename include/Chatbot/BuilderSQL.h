#pragma once
#include <string>

class BuilderSQL
{
private:
	std::string sql = "";
public:
	BuilderSQL& CreateTable(const std::string& str);
	BuilderSQL& DropTable(const std::string& str);
	BuilderSQL& InsertInto(const std::string& str);
	BuilderSQL& Update(const std::string& str);
	BuilderSQL& Set(const std::string& str);
	BuilderSQL& Values(const std::string& str);
	BuilderSQL& Select(const std::string& str = "");
	BuilderSQL& From(const std::string& str);
	BuilderSQL& Delete(const std::string& str = "");
	BuilderSQL& Where(const std::string& str);
	BuilderSQL& OrderBy(const std::string& str);
	BuilderSQL& GroupBy(const std::string& str);
	BuilderSQL& Having(const std::string& str);
	BuilderSQL& In(const std::string& str);
	BuilderSQL& Join(const std::string& str);
	BuilderSQL& On(const std::string& str);
	BuilderSQL& Distinct(const std::string& str);
	BuilderSQL& Begin();
	BuilderSQL& Commit();
	BuilderSQL& LeftJoin(const std::string& str);
	BuilderSQL& operator()(const std::string& str);
	BuilderSQL& Terminate();
	std::string Build();
};