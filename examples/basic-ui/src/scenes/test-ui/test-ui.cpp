#ifdef OLD
#include "varicle.hpp"
#include "test-ui.hpp"


void TestUIScene::init() {
    ui_factory.register_event("on_pause_clicked", []() {
        std::cout << "clicked \n";
    });
    // ui_root = ui_factory.load_file("ui.json");

    ui_root         = std::make_shared<v::ui::UINode>();
    ui_root->anchor = v::ui::anchors::FullStretch;
    v::ui::Rect screen_rect = {
        0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()
    };

    ui_root->set_global_rect(screen_rect);

    // auto health_panel           = std::make_shared<v::ui::UIPanel>();
    // health_panel->anchor        = v::ui::anchors::FullStretch;
    // health_panel->pivot         = { 0.5f, 0.5f }; // Top-Right corner origin
    // health_panel->offset_left   = 20.0f;          // 20px margin from right
    // health_panel->offset_top    = 20.0f;          // 20px margin from top
    // health_panel->offset_right  = 20.0f;          // Width
    // health_panel->offset_bottom = 20.0f;          // Height
    // ui_root->add_child(health_panel);

    // auto my_button           = std::make_shared<v::ui::UIButton>("Click Me");
    // my_button->anchor        = v::ui::anchors::Center;
    // my_button->pivot         = { 0.5f, 0.5f }; // Top-Right corner origin
    // my_button->offset_right  = 140.0f;         // Width
    // my_button->offset_bottom = 50.0f;          // Height
    // my_button->on_click      = []() { std::cout << "I've been clicked!\n"; };
    // ui_root->add_child(my_button);

    auto v_box           = std::make_shared<v::ui::UIPanel>();
    v_box->bg_color      = { 0, 0, 0, 50 };
    v_box->anchor        = v::ui::anchors::FullStretch;
    v_box->pivot         = { 0.5f, 0.5f }; // Top-Right corner origin
    v_box->offset_left   = 20.0f;          // 20px margin from right
    v_box->offset_top    = 20.0f;          // 20px margin from top
    v_box->offset_right  = 20.0f;          // Width
    v_box->offset_bottom = 20.0f;          // Height
    ui_root->add_child(v_box);
    item = v_box;
}

void create_child_element(std::shared_ptr<v::ui::UINode> parent_element) {

    auto child_element           = std::make_shared<v::ui::UIPanel>();
    child_element->anchor        = v::ui::anchors::FullStretch;
    child_element->offset_left   = 20.0f; // 20px margin from right
    child_element->offset_top    = 20.0f; // 20px margin from top
    child_element->offset_right  = 20.0f; // Width
    child_element->offset_bottom = 20.0f; // Height
    parent_element->add_child(child_element);
}

void TestUIScene::update(float dt) {
    v::ui::Rect screen_rect = {
        0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()
    };

    if (ui_root) {
        ui_root->measure_layout();
        ui_root->update_layout(screen_rect);
    }

    Vector2 mouse_pos = GetMousePosition();
    bool    ui_consumed_input =
        ui_root->process_input({ mouse_pos.x, mouse_pos.y });

    if (IsKeyPressed(KEY_SPACE)) {
        create_child_element(item);
    }
    // Only pass clicks to Physics/Game if UI didn't intercept it
    // if (!ui_consumed_input && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    //     // World interaction logic...
    //     ui_root = ui_factory.load_file("ui.json");
    // }
}

void TestUIScene::render() {}

void TestUIScene::ui() {
    ui_root->draw();
}
#endif
