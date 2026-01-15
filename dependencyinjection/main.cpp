/*
Concept: Dependency Injection (DI)
----------------------------------
Intent:
    Dependencies are provided from the outside (constructor or setter),
    rather than being created internally. This reduces coupling and improves
testability.

Use case (example):
    A service that sends notifications using a pluggable transport (Email,
Console, Mock).
*/

#include <iostream>
#include <memory>
#include <string>

namespace patterns {

class INotifier {
   public:
    virtual ~INotifier() = default;
    virtual void Send(const std::string &message) = 0;
};

class ConsoleNotifier final : public INotifier {
   public:
    void Send(const std::string &message) override {
        std::cout << "[Console] " << message << "\n";
    }
};

class EmailNotifier final : public INotifier {
   public:
    void Send(const std::string &message) override {
        std::cout << "[Email] " << message << "\n";
    }
};

class OrderService {
   public:
    // Constructor injection
    explicit OrderService(std::unique_ptr<INotifier> notifier) : m_Notifier(std::move(notifier)) {
    }

    void PlaceOrder(const std::string &item) {
        // business logic...
        m_Notifier->Send("Order placed: " + item);
    }

   private:
    std::unique_ptr<INotifier> m_Notifier;
};

}  // namespace patterns

int main() {
    using namespace patterns;

    // Swap dependencies without changing OrderService:
    OrderService serviceA(std::make_unique<ConsoleNotifier>());
    serviceA.PlaceOrder("Pizza");

    OrderService serviceB(std::make_unique<EmailNotifier>());
    serviceB.PlaceOrder("Burger");
}
