#pragma once
#include "Chatbot/CommandSQL.h"

class CmdGetCameraFrame : public CommandSQL
{
public:
	CmdGetCameraFrame() = default;
	CmdGetCameraFrame(const CmdGetCameraFrame&) = delete;
	CmdGetCameraFrame& operator=(const CmdGetCameraFrame&) = delete;
	~CmdGetCameraFrame() = default;

	json::value Execute(Database& database) override;
};