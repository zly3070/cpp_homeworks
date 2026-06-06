#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
#include "Alumni.h" // 包含进之前写的Alumni类等相关函数

void loadTestData(vector<Alumni>& list);

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    // 数据
    bool show_dialog = false;
    std::string new_name, new_department, new_class,
        new_addr, new_num, new_qq, new_email;
    char new_gender = 'm';
    unsigned int new_age = 0, new_batch = 0;
    
    std::string search_keyword;

    std::vector<Alumni> alumniList;
    loadTestData(alumniList);
    sortAlumniList(alumniList);

    // ---------- 新建按钮 ----------
    auto new_button = Button("New", [&] { show_dialog = true; });  
    // 触发按钮时把show_dialog设为true，以此弹出对话框

    // ---------- 搜索输入框 ----------
    auto search_input = Input(&search_keyword, "Search...");

    // ---------- 工具栏 ---------- 
    // toolbar_container 包起 new_button 和 search_input,toolbar_renderer 决定其渲染样式
    auto toolbar_container = Container::Horizontal({new_button, search_input});
    auto toolbar_renderer = Renderer(toolbar_container, [&] {
        return window(
            text("工具栏") | bold | center,
            hbox({
                new_button->Render(),
                separator(),
                search_input->Render() | flex,
            })
        );
    });

    // ---------- 校友列表 ----------
    // 构建卡片列表

    // 当前聚焦的卡片索引
    int focused_index = 0;
    // 记录当前焦点区域
    bool focus_on_cards = false;
    
    std::vector<Component> cards;
    for (size_t i = 0; i < alumniList.size(); i++){
        auto card = Renderer([&, i]{
            // 根据是否聚焦，决定边框颜色
            auto border_style = (focused_index == i && focus_on_cards) ? border | color(Color::Yellow) : border;
            return vbox({
                text("姓名：" + alumniList[i].getName()),
                text("届级：" + std::to_string(alumniList[i].getBatch())),
                text("系：" + alumniList[i].getDepartment()),
                text("班级：" + alumniList[i].getClassName()),
            }) | border_style | size(HEIGHT,EQUAL,6);
        }) | focus;
        cards.push_back(card);
    }

    auto cards_layout = Container::Vertical(cards); // 先创建包住所有cards的竖向组件

    //auto cards_container = Container::Vertical(cards);
    // cards_container |= focus;

    // ---------- 键盘事件处理 ----------
    auto handle_event = CatchEvent(cards_layout, [&](Event event){
        if (event == Event::ArrowUp){
            if (!cards.empty()){
                focused_index = (focused_index - 1 + cards.size()) % cards.size();
            }
            return true;
        }
        if (event == Event::ArrowDown){
            if (!cards.empty()){
                focused_index = (focused_index + 1) % cards.size();    
            }
            return true;
        }
        if (event == Event::Return && focused_index >= 0 && 
            focused_index < cards.size()){
                // 焦点在cards_layout中时，按enter选中该card
                // 接下去应有相应函数，用于修改各项属性
                return true;
            }
            return false;
    });

    // ---------- 主容器 ----------
    auto main_container = Container::Vertical({toolbar_container, handle_event});

    // ---------- 主渲染 ----------
    auto main_renderer = Renderer(main_container, [&] {
        // 计算当前焦点的滚动位置
        float scroll_pos = cards.empty() ? 0.0f : (float)focused_index / cards.size();
        // 让焦点位于可视区域中间偏上的位置（避免太靠底）
        float adjusted_scroll = std::clamp(scroll_pos - 0.2f, 0.0f, 1.0f);
        
        return vbox(
            toolbar_renderer->Render() | size(HEIGHT, EQUAL, 5),
            window(
                text("校友列表") | bold | center,
                handle_event->Render() 
                | vscroll_indicator 
                | focusPositionRelative(0.0f, adjusted_scroll)
                | frame  
                | flex
            ) | flex
        );
    });

    auto global_handler = CatchEvent(main_renderer, [&](Event event) {
        if (event == Event::Tab) {
            if (focus_on_cards) {
                    toolbar_container->TakeFocus();
                    focus_on_cards = false;
            } else {
                    handle_event->TakeFocus();
                    focus_on_cards = true;
            }
            return true;
        }
        return false;
    });

    screen.Loop(global_handler);
    return 0;
}