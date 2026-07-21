#pragma once

#include "engine/scene/scene.hpp"

#include "raylib.h"

namespace varicle {

    class Application{

            // Window configuration variables that a derived game can tweak in its constructor
            int m_window_width = 1280;
            int m_window_height = 720;
            const char* m_window_title = "My Raylib Engine Game";

        public:
            Application() = default;
            virtual ~Application() = default;

            virtual void on_init() = 0; 
            virtual void on_shutdown() = 0;

            void run();
            void change_scene(std::string scene_id);
            void quit();


    };
}
