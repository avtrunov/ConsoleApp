#include "Chatbot/FTXUI.h"

void FTXUI::Input(const unsigned id, std::string& str)
{
    std::stringstream buffer;
    buffer << '#' << std::setfill('0') << std::setw(4) << id << ": ";
    Message msg = { Type::Input, {buffer.str()} };

    std::unique_lock<std::mutex> lock(inputMutex);
    inputNotifier.wait(lock, [this] {return !inputQueue.empty(); });
    str = inputQueue.front();
    inputQueue.pop();
    lock.unlock();

    msg.data.front().append(str);
    history.push_back(msg);
    screen.PostEvent(ftxui::Event::Custom);
}

void FTXUI::Output(const std::stringstream& buffer)
{
    std::vector<std::string> splitStr;
    boost::split(splitStr, buffer.str(), boost::is_any_of("\n\r"), boost::token_compress_on);

    history.push_back({ Type::Output, splitStr });
    screen.PostEvent(ftxui::Event::Custom);
}

void FTXUI::Run()
{
    using namespace ftxui;

    std::string inputStr;
    float focus_y = 1.0f;
    ftxui::InputOption inputOption = ftxui::InputOption();

    inputOption.on_enter = [&]()
    {
        boost::trim(inputStr);
        if (!inputStr.empty())
        {
            {
                std::lock_guard<std::mutex> lock(inputMutex);
                inputQueue.push(inputStr);
            }
            inputNotifier.notify_one();
            inputStr.clear();
        }
    };
    ftxui::Component inputAdd = ftxui::Input(&inputStr, "Enter your query", inputOption);
    ftxui::Component sliderY = ftxui::Slider("", &focus_y, 0.f, 1.f, 0.01f);

    auto renderHistory = [&]()
    {
        ftxui::Elements lines;
        for (const auto& msg : history)
        {
            if (msg.type == Type::Input)
            {
                for (const auto& line : msg.data)
                {
                    lines.push_back(text(line) | color(Color::LightYellow3));
                }
            }
            else if (msg.type == Type::Output)
            {
                for (const auto& line : msg.data)
                {
                    lines.push_back(hbox({ filler(),text(line) }));
                }
            }
        }
        return lines;
    };

    auto renderer = ftxui::Renderer(
        ftxui::Container::Vertical({ inputAdd,sliderY, }),
        [&]()
        {
            auto historyWindow = vbox(renderHistory()) | focusPositionRelative(0, focus_y) | frame | flex;
            return vbox({
                historyWindow,
                separator(),
                sliderY->Render(),
                separator(),
                hbox({text(">"),inputAdd->Render()}),
                }) |
                border;
        });

    screen.Loop(renderer);
}