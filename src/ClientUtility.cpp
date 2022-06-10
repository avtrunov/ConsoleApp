#include "Chatbot/ClientUtility.h"

	void ChatbotUtility::DisplayJsonAsText(const json::value& jsonData, const std::string& prefix)
	{
		if (jsonData.is_string())
		{
			buffer << prefix << to_utf8string(jsonData.as_string()) << '\n';
		}
		else
		{
			buffer << "Cannot unpack text data.\n";
		}
	}

	void ChatbotUtility::DisplayJsonAsImage(const json::value& jsonData)
	{
		if (!jsonData.is_string())
		{
			buffer << "Cannot decompress an image.\n";
			return;
		}
		else
		{
			std::vector<uchar> encodedImage = from_base64(jsonData.as_string());

			cv::Mat image = cv::imdecode(encodedImage, cv::IMREAD_COLOR);
			if (image.empty())
			{
				buffer << "Cannot decompress an image.\n";
				return;
			}
			cv::namedWindow("Camera shot", cv::WINDOW_AUTOSIZE);
			cv::imshow("Camera shot", image);
			cv::waitKey(0);
			cv::destroyWindow("Camera shot");
		}
		//SaveImage(image);
	}

	/*
	void ChatbotUtility::SaveImage(const cv::Mat& image)
	{
		std::cout << "Сохранить изображение? Нажмите Enter для сохранения изображения\n";
		if (_getch() == 13)
		{
			std::string filename;
			do
			{
				std::cout << "Имя изображения не должно содержать следующих символов: \\/:*?\"<>|\nВведите имя файла: ";
				std::getline(std::cin, filename);
			} while (boost::regex_search(filename, boost::regex("[\\/\\*\\:\\?\"\\>\\<\\|\\\\]")));

			if (cv::imwrite(IMAGE_PATH + filename + ".jpg", image))
			{
				std::cout << "Изображение успешно сохранено!\n";
				return;
			}
			std::cout << "Не получилось сохранить сообщение.\n";
		}
	}
	*/

	std::vector<TableRow> ChatbotUtility::ParseCSV(const std::string& jsonData) const 
	{
		std::vector<std::string> tableRows;
		boost::split(tableRows, jsonData, boost::is_any_of("\n"), boost::token_compress_on);
		std::vector<TableRow> result(tableRows.size() - 1);

		for (unsigned i = 0; i < result.size(); i++)
		{
			std::vector<std::string> row;
			boost::split(row, tableRows[i], boost::is_any_of(","), boost::token_compress_on);
			for (unsigned j = 0; j < row.size(); j++)
			{
				result[i].push_back(row[j]);
			}
		}
		return result;
	}

	void ChatbotUtility::FormattedTableOutput(const std::vector<TableRow>& rows)
	{
		Table table;
		for (const auto& row : rows)
		{
			table.add_row(row);
		}
		for (size_t i = 0; i < rows[0].size(); ++i)
		{
			table[0][i].format()
				.font_align(FontAlign::center)
				.font_style({ FontStyle::bold });
		}
		buffer << table << '\n';
	}

	void ChatbotUtility::DisplayJsonAsTable(const json::value& jsonData)
	{
		if (!jsonData.is_string())
		{
			buffer << "Cannot unpack a table.\n";
			return;
		}
		std::string jsonAsStr = to_utf8string(jsonData.as_string());
		auto tableData = ParseCSV(jsonAsStr);
		if (tableData.empty())
		{
			buffer << to_utf8string(jsonData.as_string());
		}
		else
		{
			FormattedTableOutput(tableData);
		}

		//SaveTable(jsonData.as_string());
	}

	/*
	void ChatbotUtility::SaveTable(const std::string& table)
	{
		std::cout << "Сохранить таблицу? Нажмите Enter для сохранения таблицы\n";
		if (_getch() == 13)
		{
			std::string filename;
			do
			{
				std::cout << "Имя таблицы не должно содержать следующих символов: \\/:*?\"<>|\nВведите имя файла: ";
				std::getline(std::cin, filename);
			} while (boost::regex_search(filename, boost::regex("[\\/\\*\\:\\?\"\\>\\<\\|\\\\]")));

			std::wofstream outfile(TABLE_PATH + filename + ".csv", std::ios::trunc);
			if (!outfile.is_open())
			{
				std::cout << "Не получилось создать файл.\n";
				return;
			}

			outfile.imbue(std::locale("ru_RU.UTF8"));
			if (outfile << table)
			{
				std::cout << "Таблица успешно сохранена!\n";
			}
			else
			{
				std::cout << "Во время записи возникли ошибки.\n";
			}
			outfile.close();
		}
		std::cout << '\n';
	}
	*/
	void ChatbotUtility::UnpackJson(const unsigned id, const json::value& request, const json::value& responce)
	{
		buffer << "\n#" << std::setfill('0') << std::setw(4) << id << ": " << to_utf8string(request.at(U("data")).as_string()) << '\n';
		if (responce.is_null())
		{
			buffer << "Cannot unpack the message : no data.\n";
			return;
		}
		const auto& type = responce.at(U("type")).as_string();
		json::value data = responce.at(U("data"));

		if (type == L"text")
		{
			DisplayJsonAsText(data);
		}
		else if (type == L"table")
		{
			DisplayJsonAsTable(data);
		}
		else if (type == L"image")
		{
			DisplayJsonAsImage(data);
		}
		else
		{
			buffer << "Cannot unpack the message : unknown data type.\n";
		}
	}

	std::stringstream ChatbotUtility::GetBuffer()
	{
		return std::move(buffer);
	}