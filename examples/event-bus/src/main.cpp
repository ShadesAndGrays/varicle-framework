#include "varicle.hpp"

struct GreetingEvent {
    std::string greeting = "Hello";
};

int main() {
    using namespace varicle::event;

    EventBus bus;
    auto id = bus.subscribe<GreetingEvent>([](const GreetingEvent &event) {
            std::cout << event.greeting <<std::endl;
    });
    auto second_id = bus.subscribe<GreetingEvent>([](const GreetingEvent &event) {
            std::cout << "Oh! " << event.greeting <<std::endl;
    });

auto event = GreetingEvent{};
    bus.publish<GreetingEvent>(event);

    bus.defer<GreetingEvent>({.greeting="Bonjour"});

    bus.publish<GreetingEvent>({.greeting="Aloha"});

    bus.defer<GreetingEvent>({.greeting="Otutu oma"});

    bus.flush();

    return 0;
}
