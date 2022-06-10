#pragma once
#include <string>

namespace Table
{
    struct Group
    {
        int id = 0;
        std::string name = "";
    };

    struct Student
    {
        int id = 0;
        std::string lastName = "";
        std::string initials = "";
    };

    struct Task
    {
        int id = 0;
        std::string description = "";
    };

    struct Variant
    {
        int id = 0;
        std::string description = "";
    };
}

struct TableData
{
    Table::Task task;
    Table::Variant variant;
    Table::Group group;
    Table::Student student;
};