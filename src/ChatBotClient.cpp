#include "Chatbot/ChatBotClient.h"

using namespace Concurrency;

pplx::task<json::value> ClientHandler::SendDataToServer(method method, const json::value& sendData,const utility::string_t& uri)
{
	return client.request(method, uri, sendData).
		then([this](http_response& response)
			{
				auto statusCode = response.status_code();
				if (statusCode == status_codes::OK)
				{
					return response.extract_json();
				}
				else
				{
					//std::wostringstream buffer;
					//http_status_to_phrase(statusCode);
					//buffer << http_status_to_phrase(statusCode).id << ': ' << http_status_to_phrase(statusCode).phrase << '\n';
					return pplx::task_from_result(json::value::null());
				}
			});
}

std::wstringstream ClientHandler::GetBuffer()
{
	return std::move(buffer);
}