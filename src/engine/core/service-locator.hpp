#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace varicle {

class ServiceLocator {
  private:
    // generic storage
    struct ServiceContainerBase {
        virtual ~ServiceContainerBase() = default;
    };

    template <typename T>
    struct ServiceContainer : public ServiceContainerBase {
        std::unique_ptr<T> instance;
        ServiceContainer(std::unique_ptr<T> inst) : instance(std::move(inst)) {}
    };

    static inline std::
        unordered_map<std::type_index, std::unique_ptr<ServiceContainerBase>>
            s_services;

    // Track registration order to ensure safe LIFO destruction
    static inline std::vector<std::type_index> s_registration_order;

  public:
    // Wrap and pass ownership of a unique_ptr to the locator
    template <typename T> static void provide(std::unique_ptr<T> service) {
        s_services[typeid(T)] =
            std::make_unique<ServiceContainer<T>>(std::move(service));
    }
    template <typename T> static bool has() {
        return s_services.contains(typeid(T));
    }

    template <typename T> static T& get() {
        auto it = s_services.find(typeid(T));

        assert(
            it != s_services.end() && "Requested service was never provided!"
        );

        // Cast the container back, take a peek inside the container and send
        // the address of the reference auto container = static_cast
        // <ServiceContainer<T>>(it->second);

        auto* container = static_cast<ServiceContainer<T>*>(it->second.get());
        return *(container->instance);
    }

    // Explicitly destroy a specific service
    template <typename T> static void remove() {
        s_services.erase(typeid(T)); // Automatically calls the destructor of T!
        auto it = std::find(
            s_registration_order.begin(), s_registration_order.end(), typeid(T)
        );
        if (it != s_registration_order.end())
            s_registration_order.erase(it);
    }

    static inline void shutdown() {
        for (auto it = s_registration_order.rbegin();
             it != s_registration_order.rend();
             ++it) {
            s_services.erase(*it);
        }
        s_registration_order.clear();
        s_services.clear();
    }
};
}; // namespace varicle
