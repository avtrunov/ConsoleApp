#include "Chatbot\ChatBotServer.h"
#include <chrono>
#include <thread>

using namespace utility::conversions;

void DisplayJson(const json::value& jvalue, const utility::string_t& prefix)
{
	auto type = jvalue.at(U("type")).as_string();
	ucout << prefix << type << '\n';
	if (type != L"image")
	{
		ucout << jvalue.at(U("data")).as_string() << '\n';
	}
}

ServerHandler::ServerHandler() :listener(L"http://localhost/chatbotdemo"),base{}
{
	SupportMethods();
}

ServerHandler::ServerHandler(utility::string_t uri) : listener(uri), base{}
{
	SupportMethods();  
}

void ServerHandler::Listening()
{
	ucout << L"Listening at " << listener.uri().to_string() << '\n';
	listener.open().wait();
}

void ServerHandler::Shutdown()
{
	ucout << L"Shutting down listening at " << listener.uri().to_string() << '\n';
	listener.close().wait();
}

void ServerHandler::SupportMethods()
{
	listener.support(methods::POST, [this](http_request request) {HandlePOST(request); });
}

void ServerHandler::HandleRequest(http_request request, std::function<void(const json::value&, json::value&)> handleMethod)
{
	std::cout << "Handle request thread id: " << std::this_thread::get_id() << '\n';

	json::value sendJson;
	try
	{
		json::value receivedJson = request.extract_json().get();
		if (!receivedJson.is_null())
		{
			std::cout << "Process thread id: " << std::this_thread::get_id() << '\n';
			DisplayJson(receivedJson, L"Received: ");
			handleMethod(receivedJson, sendJson);
			DisplayJson(sendJson, L"Send: ");
			request.reply(status_codes::OK, sendJson);
		}
		else
		{
			request.reply(status_codes::BadRequest);
		}
	}
	catch (const http_exception& err)
	{
		std::cout << err.what();
		request.reply(status_codes::BadRequest);
	}
}

void ServerHandler::HandlePOST(http_request request)
{
	ucout << "Server handle POST\n";
	HandleRequest(request,
		[this](const json::value& receivedData, json::value& sendData)
		{
			std::wstring msg = receivedData.at(U("data")).as_string();
			sendData = base.Process(to_utf8string(msg));
		});
}