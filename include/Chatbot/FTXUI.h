#pragma once
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <queue>
#include <iomanip>
#include <concurrent_vector.h>
#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>       // for Slider, Renderer, Vertical
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive
#include <ftxui/dom/elements.hpp>  // for Elements, Element, operator|, separator, text, focusPositionRelative, size, border, flex, frame, bgcolor, gridbox, vbox, EQUAL, center, HEIGHT, WIDTH
#include <ftxui/screen/color.hpp>// for Color
#include <boost/algorithm/string.hpp>

using namespace concurrency;

class FTXUI
{
private:
    enum class Type : bool { Input, Output };
    struct Message
    {
        Type type;
        std::vector<std::string> data;
    };
    std::queue<std::string> inputQueue;
    concurrent_vector<Message> history;
    std::condition_variable inputNotifier;
    std::mutex inputMutex;
    ftxui::ScreenInteractive screen;
public:
    FTXUI() :screen(ftxui::ScreenInteractive::Fullscreen()) {}
    FTXUI(const FTXUI&) = delete;
    FTXUI& operator=(FTXUI&) = delete;
    ~FTXUI() = default;

    void Input(const unsigned id, std::string& str);
    void Output(const std::stringstream& buffer);
    void Run();
};