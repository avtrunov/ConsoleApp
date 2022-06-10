#pragma once
#include <thread>
#include <iomanip>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Chatbot/ChatBotClient.h"
#include "Chatbot/ClientUtility.h"

using namespace utility::conversions;

template <class UI>
class ClientLogic
{
private:
	struct ClientPackage
	{
		unsigned int id = 0;
		json::value request = json::value::null();
		pplx::task<json::value> responseTask;
	};
	std::mutex mtx;
	std::condition_variable requestNotifier;
	bool clientRun = true;
	std::queue<ClientPackage> messageQueue;
	UI printer;
public:
	ClientLogic() = default;
	ClientLogic(ClientLogic&) = delete;
	ClientLogic& operator=(ClientLogic&) = delete;
	~ClientLogic();

	void CreateRequest();
	void ProcessResponse();
	void Execute();
	ClientPackage CreateMessage();
};

template <class UI>
ClientLogic<UI>::~ClientLogic()
{
	clientRun = false;
}

template <class UI>
typename ClientLogic<UI>::ClientPackage ClientLogic<UI>::CreateMessage()
{
	static unsigned id = 1;
	std::string str;
	printer.Input(id, str);
	str = boost::regex_replace(str, boost::regex("[\\s\n\r\t]+"), " ");

	json::value send = json::value::object();
	send[U("type")] = json::value(U("text"));
	send[U("data")] = json::value(to_string_t(str));

	ClientPackage pack;
	pack.id = id++;
	pack.request = send;
	return pack;
}

template <class UI>
void ClientLogic<UI>::CreateRequest()
{
	try
	{
		http_client_config config;
		config.set_timeout(std::chrono::seconds(5));

		ClientHandler handler(config);

		while (clientRun)
		{
			ClientPackage package = CreateMessage();
			package.responseTask = handler.SendDataToServer(methods::POST, package.request, L"/chatbotdemo");
			
			{
				std::lock_guard<std::mutex> lock(mtx);
				messageQueue.push(package);
			}
			requestNotifier.notify_one();
		}
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what();
		exit(1);
	}
}

template <class UI>
void ClientLogic<UI>::ProcessResponse()
{
	ChatbotUtility unpacker;
	while (clientRun)
	{
		std::unique_lock<std::mutex> lock(mtx);
		requestNotifier.wait(lock, [this] {return !messageQueue.empty(); });

		auto package = messageQueue.front();
		try
		{
			if (package.responseTask.is_done())
			{
				messageQueue.pop();
				lock.unlock();
				unpacker.UnpackJson(package.id, package.request, package.responseTask.get());
				printer.Output(unpacker.GetBuffer());
			}
			else
			{
				messageQueue.pop();
				messageQueue.push(package);
				lock.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
			}
		}
		catch (http_exception& err)
		{
			std::stringstream buffer;
			buffer << "\n#" << std::setfill('0') << std::setw(4) << package.id << ": "
				<< to_utf8string(package.request.at(U("data")).as_string()) << '\n'
				<< "Server waiting time too long.\n";
			printer.Output(buffer);
		}
		catch (const std::exception& err)
		{
			std::cerr << err.what();
			exit(2);
		}
	}
}

template <class UI>
void ClientLogic<UI>::Execute()
{
	std::thread makeRequestThread(&ClientLogic::CreateRequest, this);
	std::thread processResponseThread(&ClientLogic::ProcessResponse, this);
	printer.Run();
	processResponseThread.join();
	makeRequestThread.join();
}