#pragma once
#include <mutex>
#include <string>
#include <sstream>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <boost/algorithm/string.hpp>

class ConsolePrinter
{
private:
	std::mutex mtx;
public:
	ConsolePrinter();
	ConsolePrinter(ConsolePrinter&) = delete;
	ConsolePrinter& operator=(ConsolePrinter&) = delete;
	~ConsolePrinter() = default;

	void Input(const unsigned id, std::string& str);
	void Output(const std::stringstream& buffer);
	void Run();
};