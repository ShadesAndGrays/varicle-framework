#include "layout-test.hpp"
#include "engine/ui/layout/hstacking.hpp"
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

    auto parent = std::make_shared<ui::UIPanel>();


    auto tim = std::make_shared<ui::UIPanel>();
    tim->padding_top = 50;
    tim->padding_right = 50;
    tim->sizing_mode = ui::SizingMode::EXACT;
    tim->bg_color = varicle::Color::Red();

    auto ben = std::make_shared<ui::UIPanel>();
    ben->padding_top = 90;
    ben->padding_right = 60;
    ben->bias = 1.0f;
    ben->sizing_mode = ui::SizingMode::FILL;
    ben->bg_color = varicle::Color::Green();

    auto samantha = std::make_shared<ui::UIPanel>();
    samantha->padding_top = 90;
    samantha->padding_right = 30;
    samantha->sizing_mode = ui::SizingMode::EXACT;
    samantha->bg_color = varicle::Color::Yellow();

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
    parent->set_layout_strategy(std::make_unique<ui::HStackingStrategy>());

    // parent->margin_top    = 10.0f;
    // parent->margin_bottom = 10.0f;
    // parent->margin_left   = 10.0f;
    // parent->margin_right  = 10.0f;

    parent->add_child(std::move(tim));
    parent->add_child(std::move(ben));
    parent->add_child(std::move(samantha));
    root->add_child(std::move(parent));

    // This would normally run in a loop of via and event callback;
    // Measure Pass
    root->measure_layout(root->layout_constraint);

    // Arrange Pass
    root->update_layout(root->get_global_rect());

    std::cout << std::format(
        "root preferred_size: {}\nparent preferred_size: {}\nchild1 "
        "preferred_size:  {}\nchild2 preferred_size:  {}\n",
        EngineVariant(root->preferred_size).to_string(),
        EngineVariant(root->get_children()[0]->preferred_size).to_string(),
        EngineVariant(
            root->get_children()[0]->get_children()[0]->preferred_size
        )
            .to_string(),
        EngineVariant(
            root->get_children()[0]->get_children()[1]->preferred_size
        )
            .to_string()
    );

    std::cout << std::format(
        "root rect: {}\nparent rect: {}\ntim rect:  {}\nben rect:  {}\n "
        "samantha rect:  {}\n",
        root->get_global_rect().to_string(),
        root->get_children()[0]->get_global_rect().to_string(),

        root->get_children()[0]
            ->get_children()[0]
            ->get_global_rect()
            .to_string(),

        root->get_children()[0]
            ->get_children()[1]
            ->get_global_rect()
            .to_string(),

        root->get_children()[0]
            ->get_children()[2]
            ->get_global_rect()
            .to_string()

    );

    // ServiceLocator::get<SceneManager>().quit();
}

void LayoutTestScene::update(float dt) {}

void LayoutTestScene::render() {

    // Render Pass
    root->draw();
}

void LayoutTestScene::ui() {}
