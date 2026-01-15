/*
Pattern: Decorator (Gamma et al.)
---------------------------------
Intent:
    Attach additional responsibilities to an object dynamically.
    Decorators provide a flexible alternative to subclassing for extending
behavior.

Use case (example):
    Add logging and timing to a service without modifying the service itself.
*/

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

namespace patterns {

class IService {
public:
  virtual ~IService() = default;
  virtual std::string Execute(const std::string &input) = 0;
};

class CoreService final : public IService {
public:
  std::string Execute(const std::string &input) override {
    return "Processed: " + input;
  }
};

class LoggingDecorator final : public IService {
public:
  explicit LoggingDecorator(std::unique_ptr<IService> inner)
      : m_Inner(std::move(inner)) {}

  std::string Execute(const std::string &input) override {
    std::cout << "[Log] input=" << input << "\n";
    const auto out = m_Inner->Execute(input);
    std::cout << "[Log] output=" << out << "\n";
    return out;
  }

private:
  std::unique_ptr<IService> m_Inner;
};

class TimingDecorator final : public IService {
public:
  explicit TimingDecorator(std::unique_ptr<IService> inner)
      : m_Inner(std::move(inner)) {}

  std::string Execute(const std::string &input) override {
    const auto start = std::chrono::high_resolution_clock::now();
    const auto out = m_Inner->Execute(input);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    std::cout << "[Timing] " << us << " us\n";
    return out;
  }

private:
  std::unique_ptr<IService> m_Inner;
};

} // namespace patterns

int main() {
  using namespace patterns;

  // Compose decorators dynamically:
  std::unique_ptr<IService> service = std::make_unique<CoreService>();
  service = std::make_unique<LoggingDecorator>(std::move(service));
  service = std::make_unique<TimingDecorator>(std::move(service));

  std::cout << service->Execute("CircuitSim") << "\n";
}
