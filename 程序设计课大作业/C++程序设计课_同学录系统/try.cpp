#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
#include "Alumni.h"

void loadTestData(vector<Alumni>& list);

using namespace ftxui;

// ============================================================
// 主函数
// ============================================================
int main() {
    auto screen = ScreenInteractive::Fullscreen();

    // ---------- 数据 ----------
    bool show_dialog = false;
    std::string new_name, new_department, new_class,
        new_addr, new_num, new_qq, new_email, new_gender_str,
        new_age_str, new_batch_str;
    char new_gender = 'm';
    unsigned int new_age = 0, new_batch = 0;

    std::string search_keyword;
    int focused_index = 0;
    bool focus_on_cards = false;

    std::vector<Alumni> alumniList;
    loadTestData(alumniList);
    sortAlumniList(alumniList);
    std::vector<Component> cards;

    // ---------- 重建卡片 ----------
    auto rebuildCards = [&]() {
        cards.clear();
        for (size_t i = 0; i < alumniList.size(); i++) {
            auto card = Renderer([&, i] {
                auto border_style = (focused_index == i && focus_on_cards)
                                    ? border | color(Color::Yellow)
                                    : border;
                auto content = vbox({
                    text("姓名：" + alumniList[i].getName()),
                    text("届级：" + std::to_string(alumniList[i].getBatch())),
                    text("系：" + alumniList[i].getDepartment()),
                    text("班级：" + alumniList[i].getClassName()),
                }) | border_style | size(WIDTH, EQUAL, 50);

                // 仅当此卡片被聚焦时加上 focus 修饰符
                // frame 看到 focus 后，会在元素将超出可视区域时自动滚动
                if (focused_index == i && focus_on_cards) {
                    content = content | focus;
                }
                return content;
            });
            cards.push_back(card);
        }
    };

    // ---------- 工具栏 ----------
    auto new_button = Button("New", [&] { show_dialog = true; });
    auto search_input = Input(&search_keyword, "Search...");

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

    // ---------- 新建对话框 ----------
    auto name_input   = Input(&new_name, "姓名");
    auto gender_input = Input(&new_gender_str, "性别(m/f)");
    auto age_input    = Input(&new_age_str, "年龄");
    auto batch_input  = Input(&new_batch_str, "届级");
    auto dept_input   = Input(&new_department, "系");
    auto class_input  = Input(&new_class, "班级");
    auto addr_input   = Input(&new_addr, "通讯地址");
    auto num_input    = Input(&new_num, "电话");
    auto qq_input     = Input(&new_qq, "QQ");
    auto email_input  = Input(&new_email, "邮箱");

    auto confirm_btn = Button("确认", [&] {
        char gender = new_gender_str.empty() ? 'm' : new_gender_str[0];
        unsigned int age = std::stoi(new_age_str);
        unsigned int batch = std::stoi(new_batch_str);

        alumniList.push_back(Alumni(new_name, gender, age, batch,
            new_department, new_class, new_addr, new_num, new_qq, new_email));

        new_name.clear(); new_gender_str.clear(); new_age_str.clear();
        new_batch_str.clear(); new_department.clear(); new_class.clear();
        new_addr.clear(); new_num.clear(); new_qq.clear(); new_email.clear();

        rebuildCards();
        sortAlumniList(alumniList);
        show_dialog = false;
    });

    auto cancel_btn = Button("取消", [&] {
        show_dialog = false;
    });

    auto dialog_buttons = Container::Horizontal({confirm_btn, cancel_btn});

    // ★★★ 关键修复：dialog 作为 Container::Vertical 管理所有输入框的焦点 ★★★
    auto dialog = Container::Vertical({
        name_input, gender_input, age_input, batch_input,
        dept_input, class_input, addr_input, num_input, qq_input, email_input,
        dialog_buttons
    });

    // ★★★ dialog 的渲染器：把 dialog（容器）传参，让事件能透传 ★★★
    auto dialog_Render = Renderer(dialog, [&, name_input, gender_input, age_input,
                                            batch_input, dept_input, class_input,
                                            addr_input, num_input, qq_input,
                                            email_input, confirm_btn, cancel_btn] {
        return window(
            text(" 录入新校友 ") | bold | center,
            vbox({
                name_input->Render(),
                gender_input->Render(),
                age_input->Render(),
                batch_input->Render(),
                dept_input->Render(),
                class_input->Render(),
                addr_input->Render(),
                num_input->Render(),
                qq_input->Render(),
                email_input->Render(),
                separator(),
                hbox({
                    confirm_btn->Render(),
                    separator(),
                    cancel_btn->Render(),
                }) | center,
            })
        ) | size(WIDTH, EQUAL, 40) | size(HEIGHT, EQUAL, 16);
    });

    // ---------- 校友列表 ----------
    for (size_t i = 0; i < alumniList.size(); i++) {
        auto card = Renderer([&, i] {
            auto border_style = (focused_index == i && focus_on_cards) ? border | color(Color::Yellow) : border;
            auto content = vbox({
                text("姓名：" + alumniList[i].getName()),
                text("届级：" + std::to_string(alumniList[i].getBatch())),
                text("系：" + alumniList[i].getDepartment()),
                text("班级：" + alumniList[i].getClassName()),
            }) | border_style | size(HEIGHT, EQUAL, 6);

            // ★ 仅当此卡片被聚焦时加上 focus 修饰符
            //   frame 看到 focus 后，会在元素将超出可视区域时自动滚动
            if (focused_index == i && focus_on_cards) {
                content = content | focus;
            }
            return content;
        });
        cards.push_back(card);
    }

    auto cards_layout = Container::Vertical(cards);

    // ---------- 键盘事件处理 ----------
    auto handle_event = CatchEvent(cards_layout, [&](Event event) {
        if (event == Event::ArrowUp) {
            if (!cards.empty()) {
                focused_index = (focused_index - 1 + cards.size()) % cards.size();
            }
            return true;
        }
        if (event == Event::ArrowDown) {
            if (!cards.empty()) {
                focused_index = (focused_index + 1) % cards.size();
            }
            return true;
        }
        if (event == Event::Return && focused_index >= 0 &&
            focused_index < (int)cards.size()) {
            return true;
        }
        return false;
    });

    // ---------- 主容器（dialog 也加入组件树） ----------
    auto main_container = Container::Vertical({
        toolbar_container,
        handle_event,
        dialog,   // dialog 加入组件树，才能接收事件
    });

    // ---------- 主渲染 ----------
    auto main_renderer = Renderer(main_container, [&] {
        if (show_dialog) {
            return dialog_Render->Render() | center;
        } else {
            return vbox(
                toolbar_renderer->Render() | size(HEIGHT, EQUAL, 5),
                window(
                    text("校友列表") | bold | center,
                    // ★ 移除 focusPositionRelative，仅靠 frame 自动滚动
                    //   frame 会检测 focus 元素的位置，仅在它即将移出可视区域时滚动
                    handle_event->Render()
                        | vscroll_indicator
                        | frame
                        | flex
                ) | flex
            );
        }
    });

    // ---------- 全局事件 ----------
    auto global_handler = CatchEvent(main_renderer, [&](Event event) {
        // 对话框打开时：让 dialog 获得焦点，并让 dialog 自己处理事件
        if (show_dialog) {
            dialog->TakeFocus();
            return false;  // 不拦截，让 dialog 内部的 Container::Vertical 处理
        }

        // 列表模式下的 Tab 切换
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
