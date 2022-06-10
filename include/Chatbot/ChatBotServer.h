#pragma once
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "Chatbot/Logic.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class ServerHandler
{
private:
	http_listener listener;
	Logic<Teacher> base;
	void SupportMethods();
	void HandleRequest(http_request request, std::function<void(const json::value&, json::value&)> handleMethod);
	void HandlePOST(http_request request);
public:
	ServerHandler();
	explicit ServerHandler(utility::string_t uri);
	~ServerHandler() = default;

	void Listening();
	void Shutdown();
};