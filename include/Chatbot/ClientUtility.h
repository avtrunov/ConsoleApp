#pragma once
#include <cpprest/json.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iomanip>
#include <tabulate/table.hpp>
#include "ChatbotConfig.h"
#include "Chatbot/ConsolePrinter.h"
#include "Chatbot/FTXUI.h"

using namespace tabulate;
using TableRow = std::vector<std::variant<std::string, tabulate::Table>>;
using namespace web;
using namespace utility::conversions;

class ChatbotUtility
{
private:
	std::stringstream buffer;
	//void SaveTable(const std::string& table);
	//void SaveImage(const cv::Mat& image);
	void DisplayJsonAsImage(const json::value& jsonData);
	void DisplayJsonAsTable(const json::value& jsonData);
	void DisplayJsonAsText(const json::value& jsonData, const std::string& prefix = "");
	std::vector<TableRow> ParseCSV(const std::string& jsonData) const;
	void FormattedTableOutput(const std::vector<TableRow>& rows);
public:
	ChatbotUtility() = default;
	ChatbotUtility(ChatbotUtility&) = delete;
	ChatbotUtility& operator=(ChatbotUtility&) = delete;
	~ChatbotUtility() = default;

	void UnpackJson(const unsigned id, const json::value& request, const json::value& responce);
	std::stringstream GetBuffer();
};