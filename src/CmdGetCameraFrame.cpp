#include "Chatbot/CmdGetCameraFrame.h"
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/logger.hpp>

json::value CmdGetCameraFrame::Execute(Database& database)
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
	std::vector<uchar> encodedFrame;
	cv::VideoCapture camera;
	cv::Mat frame;
	if (!camera.open(0))
	{
		errMessage = "Cannot connect to the camera.\n";
		return json::value::null();
	}
	if (!camera.read(frame))
	{
		errMessage = "Cannot read a frame.\n";
		return json::value::null();
	}
	if (!cv::imencode(".jpg", frame, encodedFrame))
	{
		errMessage = "Cannot compress a frame.\n";
		return json::value::null();
	}

	json::value result = json::value::object();
	result[U("type")] = json::value(U("image"));
	result[U("data")] = json::value(to_base64(encodedFrame));
	return result;
}