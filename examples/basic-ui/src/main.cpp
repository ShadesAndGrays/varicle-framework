#include "varicle.hpp"

namespace v = varicle;

class MainScene : public v::Scene {
  private:
    varicle::ui::UIFactory         ui_factory;
    std::shared_ptr<v::ui::UINode> ui_root;

  public:
    void init() override;

    void update(float dt) override;

    void render() override;

    void ui() override;

    void deinit() override {}
};

class Game : public v::Application {

  public:
    void on_init() override {
        auto& sm = v::ServiceLocator::get<v::SceneManager>();
        sm.register_scene("main", []() {
            return std::make_unique<MainScene>();
        });

        sm.switch_to_scene("main");
    }

    void on_shutdown() override {}
};

void MainScene::init() {
    ui_factory.register_event("on_pause_clicked", []() {
            std::cout << "clicked \n";

        });
    ui_root = ui_factory.load_file("ui.json");

    // ui_root         = std::make_shared<v::ui::UINode>();
    // ui_root->anchor = v::ui::anchors::FullStretch;
    //
    // auto health_panel           = std::make_shared<v::ui::UIPanel>();
    // health_panel->anchor        = v::ui::anchors::TopRight;
    // health_panel->pivot         = { 0.5f, 0.5f }; // Top-Right corner origin
    // health_panel->offset_left   = 20.0f;          // 20px margin from right
    // health_panel->offset_top    = 20.0f;          // 20px margin from top
    // health_panel->offset_right  = 20.0f;          // Width
    // health_panel->offset_bottom = 20.0f;          // Height
    // ui_root->add_child(health_panel);
    //
    // auto my_button           = std::make_shared<v::ui::UIButton>("Click Me");
    // my_button->anchor        = v::ui::anchors::Center;
    // my_button->pivot         = { 0.5f, 0.5f }; // Top-Right corner origin
    // my_button->offset_right  = 140.0f;         // Width
    // my_button->offset_bottom = 50.0f;          // Height
    // my_button->on_click      = []() { std::cout << "I've been clicked!\n"; };
    // ui_root->add_child(my_button);
}

void MainScene::update(float dt) {
    v::ui::Rect screen_rect = {
        0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()
    };

    if (ui_root)
        ui_root->update_layout(screen_rect);

    Vector2 mouse_pos = GetMousePosition();
    bool    ui_consumed_input =
        ui_root->process_input({ mouse_pos.x, mouse_pos.y });

    // Only pass clicks to Physics/Game if UI didn't intercept it
    if (!ui_consumed_input && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // World interaction logic...
        ui_root = ui_factory.load_file("ui.json");
    }
}

void MainScene::render() {}

void MainScene::ui() {
    ui_root->draw();
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    Game game;
    game.run();
    return 0;
}
