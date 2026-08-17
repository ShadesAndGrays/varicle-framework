#include "scenes/layout-test/layout-test.hpp"
#include "scenes/test-ui/test-ui.hpp"
#include "varicle.hpp"

namespace v = varicle;

// #define OLD

class Game : public v::Application {

  public:
    void on_init() override {
        auto& sm = v::ServiceLocator::get<v::SceneManager>();

#ifdef OLD
        sm.register_scene("test-ui", []() {
            return std::make_unique<TestUIScene>();
        });
#endif

        sm.register_scene("layout-ui", []() {
            return std::make_unique<LayoutTestScene>();
        });

        sm.switch_to_scene("layout-ui");
    }

    void on_shutdown() override {}
};

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    Game game;
    game.run();

    return 0;
}
