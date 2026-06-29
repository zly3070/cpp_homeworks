#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
#include <sstream>
#include "Alumni.h"

using namespace ftxui;

const int PAGE_WIDTH = 80;
const std::string DATA_FILE = "data.txt";  // 数据文件名

// 搜索匹配函数：任意关键词命中任意字段即匹配
bool matchAlumni(const Alumni& a, const std::string& keyword) {
    if (keyword.empty()) return true;
    std::vector<std::string> keywords;
    std::stringstream ss(keyword);
    std::string word;
    while (ss >> word) keywords.push_back(word);

    for (const auto& kw : keywords) {
        if (a.getName().find(kw) != std::string::npos) return true;
        if (std::string(1, a.getGender()) == kw) return true;
        if (std::to_string(a.getAge()) == kw) return true;
        if (std::to_string(a.getBatch()) == kw) return true;
        if (a.getDepartment().find(kw) != std::string::npos) return true;
        if (a.getClassName().find(kw) != std::string::npos) return true;
        if (a.getAddr().find(kw) != std::string::npos) return true;
        if (a.getNum().find(kw) != std::string::npos) return true;
        if (a.getQq().find(kw) != std::string::npos) return true;
        if (a.getEmail().find(kw) != std::string::npos) return true;
    }
    return false;
}

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    AlumniList alumniList;                    // ★ 自定义链表
    // 从文件读取，不再用 loadTestData
    loadFromFile(alumniList, DATA_FILE);
    if (alumniList.empty()) {        // 文件为空时加载测试数据
        loadTestData(alumniList);
    }
    sortAlumniList(alumniList);

    bool show_dialog = false;
    bool is_edit_mode = false;
    int edit_index = -1;
    int selected = 0;
    bool focus_on_list = false;

    std::string new_name, new_department, new_class,
        new_addr, new_num, new_qq, new_email,
        new_gender_str, new_age_str, new_batch_str;
    std::string search_keyword;
    std::string error_msg;                    // ★ 校验错误提示

    auto getVisibleIndices = [&]() -> std::vector<int> {
        std::vector<int> indices;
        for (int i = 0; i < alumniList.size(); i++) {        // ★ size() 返回 int
            if (matchAlumni(alumniList.at(i), search_keyword)) {  // ★ at(i)
                indices.push_back(i);
            }
        }
        return indices;
    };

    // ---------- 工具栏 ----------
    auto new_button = Button("New", [&] {
        is_edit_mode = false;
        error_msg.clear();                    // ★ 清空提示
        show_dialog = true;
    });
    auto search_input = Input(&search_keyword, "Search...");
    auto toolbar = Container::Horizontal({new_button, search_input});

    // ---------- 对话框组件 ----------
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

    auto clearInputs = [&] {
        new_name.clear(); new_gender_str.clear(); new_age_str.clear();
        new_batch_str.clear(); new_department.clear(); new_class.clear();
        new_addr.clear(); new_num.clear(); new_qq.clear(); new_email.clear();
    };

    auto fillInputs = [&](const Alumni& a) {
        new_name = a.getName();
        new_gender_str = std::string(1, a.getGender());
        new_age_str = std::to_string(a.getAge());
        new_batch_str = std::to_string(a.getBatch());
        new_department = a.getDepartment();
        new_class = a.getClassName();
        new_addr = a.getAddr();
        new_num = a.getNum();
        new_qq = a.getQq();
        new_email = a.getEmail();
    };

    auto confirm_btn = Button("确认", [&] {
        // ★ 先做合法性校验
        error_msg = validateAlumniInput(
            new_name, new_gender_str, new_age_str, new_batch_str,
            new_num, new_qq, new_email);
        if (!error_msg.empty()) {
            return;   // 校验不通过，保持对话框
        }

        char gender = new_gender_str[0];
        unsigned int age = std::stoi(new_age_str);
        unsigned int batch = std::stoi(new_batch_str);

        Alumni newData(new_name, gender, age, batch,
            new_department, new_class, new_addr, new_num, new_qq, new_email);

        if (is_edit_mode && edit_index >= 0 && edit_index < alumniList.size()) {
            alumniList.set(edit_index, newData);     // ★ set
        } else {
            alumniList.push_back(newData);
        }

        sortAlumniList(alumniList);
        saveToFile(alumniList, DATA_FILE);  // ★ 保存到文件
        clearInputs();
        show_dialog = false;
        is_edit_mode = false;
        edit_index = -1;
    });

    auto cancel_btn = Button("取消", [&] {
        clearInputs();
        error_msg.clear();
        show_dialog = false;
        is_edit_mode = false;
        edit_index = -1;
    });

    auto dialog = Container::Vertical({
        name_input, gender_input, age_input, batch_input,
        dept_input, class_input, addr_input, num_input,
        qq_input, email_input,
        Container::Horizontal({confirm_btn, cancel_btn}),
    });

    // ---------- 卡片列表 ----------
    auto card_list = Renderer([&] {
        auto visible = getVisibleIndices();

        if (selected >= (int)visible.size())
            selected = visible.empty() ? 0 : (int)visible.size() - 1;

        if (visible.empty()) {
            return vbox({
                filler(),
                text("暂无校友数据，按  New 添加") | dim | center,
                filler(),
            }) | flex;
        }

        Elements card_elements;
        for (size_t vi = 0; vi < visible.size(); vi++) {
            auto& a = alumniList.at(visible[vi]);            // ★ at()
            auto content = vbox({
                text("姓名：" + a.getName()) | bold,
                text("性别：" + std::string(a.getGender() == 'm' ? "m" : "f")),
                text("年龄：" + std::to_string(a.getAge())),
                text("届级：" + std::to_string(a.getBatch())),
                text("系　：" + a.getDepartment()),
                text("班级：" + a.getClassName()),
                text("地址：" + a.getAddr()),
                text("电话：" + a.getNum()),
                text("QQ　：" + a.getQq()),
                text("邮箱：" + a.getEmail()),
            });

            if ((int)vi == selected && focus_on_list) {
                content = content | border | inverted | focus;
            } else {
                content = content | border;
            }
            content = content | size(WIDTH, EQUAL, PAGE_WIDTH - 4);
            card_elements.push_back(hbox({content}) | center);
        }

        return vbox(card_elements) | vscroll_indicator | frame | flex;
    });

    auto main_container = Container::Vertical({
        toolbar,
        dialog,
    });

    auto main_renderer = Renderer(main_container, [&] {
        if (show_dialog) {
            dialog->TakeFocus();
            auto dialog_title = is_edit_mode
                ? text(" 编辑校友信息 ") | bold | center
                : text(" 录入新校友 ") | bold | center;

            auto dialog_box = window(
                dialog_title,
                vbox({
                    hbox({text("姓名：") | size(WIDTH, EQUAL, 10), name_input->Render() | flex}),
                    hbox({text("性别：") | size(WIDTH, EQUAL, 10), gender_input->Render() | flex}),
                    hbox({text("年龄：") | size(WIDTH, EQUAL, 10), age_input->Render() | flex}),
                    hbox({text("届级：") | size(WIDTH, EQUAL, 10), batch_input->Render() | flex}),
                    hbox({text("系　：") | size(WIDTH, EQUAL, 10), dept_input->Render() | flex}),
                    hbox({text("班级：") | size(WIDTH, EQUAL, 10), class_input->Render() | flex}),
                    hbox({text("地址：") | size(WIDTH, EQUAL, 10), addr_input->Render() | flex}),
                    hbox({text("电话：") | size(WIDTH, EQUAL, 10), num_input->Render() | flex}),
                    hbox({text("QQ　：") | size(WIDTH, EQUAL, 10), qq_input->Render() | flex}),
                    hbox({text("邮箱：") | size(WIDTH, EQUAL, 10), email_input->Render() | flex}),
                    // ★ 校验错误提示行
                    error_msg.empty()
                        ? text("")
                        : text("✗ " + error_msg) | color(Color::Red) | center,
                    separator(),
                    hbox({
                        confirm_btn->Render() | flex,
                        separator(),
                        cancel_btn->Render() | flex,
                    }) | center,
                })
            ) | size(WIDTH, EQUAL, 40) | border;
            return dialog_box | center | clear_under;
        }

        auto toolbar_title = focus_on_list
            ? text("工具栏（Tab 切换焦点）") | bold | center | dim
            : text("工具栏 [当前焦点]") | bold | center | color(Color::Green);

        auto visible_count = (int)getVisibleIndices().size();
        std::string count_info = search_keyword.empty()
            ? "（共 " + std::to_string(visible_count) + " 条）"
            : "（搜索到 " + std::to_string(visible_count) + " 条）";

        auto list_title = focus_on_list
            ? text("校友列表 [当前焦点]" + count_info + "（↑↓ 选择，Enter 编辑，d 删除）") | bold | center | color(Color::Green)
            : text("校友列表 " + count_info + "（Tab 切换焦点）") | bold | center | dim;

        auto page = vbox({
            window(
                toolbar_title,
                hbox({
                    new_button->Render(),
                    separator(),
                    search_input->Render() | flex,
                })
            ) | size(HEIGHT, EQUAL, 5),
            window(
                list_title,
                card_list->Render() | flex
            ) | flex,
        }) | size(WIDTH, EQUAL, PAGE_WIDTH);

        return hbox({filler(), page, filler()});
    });

    auto global = CatchEvent(main_renderer, [&](Event event) {
        if (show_dialog) {
            if (event == Event::Escape) {
                clearInputs();
                error_msg.clear();
                show_dialog = false;
                is_edit_mode = false;
                edit_index = -1;
                return true;
            }
            return false;
        }

        if (!focus_on_list && (event == Event::ArrowUp || event == Event::ArrowDown)) {
            return true;
        }

        if (event == Event::Tab) {
            focus_on_list = !focus_on_list;
            if (!focus_on_list) {
                toolbar->TakeFocus();
            }
            return true;
        }

        if (focus_on_list) {
            auto visible = getVisibleIndices();
            if (visible.empty()) return false;

            if (event == Event::ArrowDown) {
                selected = (selected + 1) % visible.size();
                return true;
            }
            if (event == Event::ArrowUp) {
                selected = (selected - 1 + visible.size()) % visible.size();
                return true;
            }
            if (event == Event::Return) {
                int realIndex = visible[selected];
                is_edit_mode = true;
                edit_index = realIndex;
                error_msg.clear();                       // ★ 清空提示
                fillInputs(alumniList.at(realIndex));    // ★ at()
                show_dialog = true;
                return true;
            }
            if (event == Event::Character('d')) {
                int realIndex = visible[selected];
                alumniList.erase(realIndex);             // ★ erase(index)
                saveToFile(alumniList, DATA_FILE);  // ★ 删除后保存
                if (selected >= (int)visible.size() - 1 && selected > 0)
                    selected--;
                return true;
            }
            if (event == Event::ArrowLeft || event == Event::ArrowRight) {
                return true;
            }
        }

        return false;
    });

    screen.Loop(global);

    // ★ 退出时再保存一次，保险
    saveToFile(alumniList, DATA_FILE);
    return 0;
}
