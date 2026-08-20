#include "layout-test.hpp"

#include "varicle.hpp"

using namespace varicle;

void LayoutTestScene::init() {
    // create root node
    root = std::make_shared<ui::UINode>();

    // set constraints
    root->layout_constraint.min_width  = 0;
    root->layout_constraint.min_width  = 0;
    root->layout_constraint.max_width  = GetScreenWidth();
    root->layout_constraint.max_height = GetScreenHeight();
    root->set_global_rect(
        { 0,
          0,
          static_cast<float>(GetScreenWidth()),
          static_cast<float>(GetScreenHeight()) }
    );

    root->set_layout_strategy(std::make_unique<ui::FillStrategy>());

    auto grand_parent       = std::make_shared<ui::UIPanel>();
    grand_parent->alignment = ui::Aligment::CENTER;
    grand_parent->set_layout_strategy(
        std::make_unique<ui::HStackingStrategy>()
    );
    grand_parent->bg_color = { 0, 0, 0, 50 };
    grand_parent->container_sizing = {ui::SizingMode::FILL,ui::SizingMode::FILL};

    auto parent       = std::make_shared<ui::UIPanel>();
    parent->alignment = ui::Aligment::CENTER;
    parent->set_layout_strategy(std::make_unique<ui::VStackingStrategy>());
    parent->bg_color    = varicle::Color::Purple();
    parent->container_sizing = {ui::SizingMode::EXACT, ui::SizingMode::FILL};
    parent->bias        = 1.0f;

    auto tim           = std::make_shared<ui::UIPanel>();
    tim->padding_top   = 50;
    tim->padding_right = 50;
    tim->bg_color      = { 0, 0, 0, 50 };
    tim->bg_color      = varicle::Color::Red();

    auto ben           = std::make_shared<ui::UIPanel>();
    ben->padding_top   = 90;
    ben->padding_right = 60;
    ben->bias          = 1.0f;
    ben->bg_color = { 0, 0, 0, 50 };
    ben->bg_color      = varicle::Color::Green();

    auto samantha           = std::make_shared<ui::UIPanel>();
    samantha->padding_top   = 90;
    samantha->padding_right = 30;
    samantha->bg_color = { 0, 0, 0, 50 };
    samantha->bg_color      = varicle::Color::Yellow();

    // create children and give them to the parent
    // auto child1            = std::make_shared<ui::UIPanel>();
    // auto child2            = std::make_shared<ui::UIPanel>();
    //
    // child1->bg_color = varicle::Color::Red();
    // child2->bg_color = varicle::Color::Blue();
    // parent->bg_color = varicle::Color{55,55,55,255};
    //
    // child2->padding_top    = 20.0f;
    // child2->padding_bottom = 20.0f;
    // child2->padding_left    = 20.0f;
    // child2->padding_right = 20.0f;
    //
    //
    //
    // child1->padding_left   = 50.0f;
    // child1->padding_bottom = 60.0f;

    // parent->padding_top    = 10.0f;
    // parent->padding_bottom = 10.0f;
    // parent->padding_left   = 10.0f;
    // parent->padding_right  = 10.0f;

    // parent->margin_top    = 10.0f;
    // parent->margin_bottom = 10.0f;
    // parent->margin_left   = 10.0f;
    // parent->margin_right  = 10.0f;

    parent->add_child(std::move(tim));
    parent->add_child(std::move(ben));
    parent->add_child(std::move(samantha));
    grand_parent->add_child(std::move(parent));
    root->add_child(std::move(grand_parent));
#define DEBUG_LAYOUT_TEST

    // This would normally run in a loop of via and event callback;
    // Measure Pass
    root->measure_layout(root->layout_constraint);

    // Arrange Pass
    root->update_layout(root->get_global_rect());

#ifdef DEBUG_LAYOUT_TEST
    std::cout << std::format(
        "root preferred_size: {}\n"
        "grand_parent preferred_size: {}\n"
        "parent preferred_size: {}\n"
        "tim preferred_size : {}\n"
        "ben preferred_size : {}\n "
        "samantha preferred_size : {}\n ",
        EngineVariant(root->preferred_size).to_string(),
        EngineVariant(root->get_children()[0]->preferred_size).to_string(),
        EngineVariant(
            root->get_children()[0]->get_children()[0]->preferred_size
        )
            .to_string(),

        EngineVariant(root->get_children()[0]
                          ->get_children()[0]
                          ->get_children()[0]
                          ->preferred_size)
            .to_string(),
        EngineVariant(root->get_children()[0]
                          ->get_children()[0]
                          ->get_children()[1]
                          ->preferred_size)
            .to_string(),

        EngineVariant(root->get_children()[0]
                          ->get_children()[0]
                          ->get_children()[2]
                          ->preferred_size)
            .to_string()
    );

    std::cout << std::format(
        "root rect: {}\n"
        "grand_parent rect: {}\n"
        "parent rect: {}\n"
        "tim rect:  {}\n"
        "ben rect:  {}\n"
        "samantha rect:  {}\n",
        root->get_global_rect().to_string(),

        root->get_children()[0]->get_global_rect().to_string(),

        root->get_children()[0]
            ->get_children()[0]
            ->get_global_rect()
            .to_string(),

        root->get_children()[0]
            ->get_children()[0]
            ->get_children()[0]
            ->get_global_rect()
            .to_string(),

        root->get_children()[0]
            ->get_children()[0]
            ->get_children()[1]
            ->get_global_rect()
            .to_string(),

        root->get_children()[0]
            ->get_children()[0]
            ->get_children()[2]
            ->get_global_rect()
            .to_string()

    );

#endif
}

void LayoutTestScene::update(float dt) {}

void LayoutTestScene::render() {

    // Render Pass
    root->draw();
    DrawCircleV({ 1280 / 2, 720 / 2 }, 10, ::RED);
}

void LayoutTestScene::ui() {}
