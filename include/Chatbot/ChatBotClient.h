#pragma once
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include "Chatbot/ConsolePrinter.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency;

class ClientHandler
{
private:
	http_client client;
	std::wstringstream buffer;
public:
	ClientHandler() : client(L"http://localhost") {}
	explicit ClientHandler(const http_client_config& options) :client(L"http://localhost", options) {}
	explicit ClientHandler(utility::string_t&& address) : client(address) {}
	explicit ClientHandler(utility::string_t&& address, const http_client_config& options) : client(address, options) {}
	ClientHandler(ClientHandler&) = delete;
	ClientHandler& operator=(ClientHandler&) = delete;
	~ClientHandler() = default;

	pplx::task<json::value> SendDataToServer(method method, const json::value& sendData, const utility::string_t& uri);
	std::wstringstream GetBuffer();
};