/*
Example: std::unique_ptr + RAII + std::move + std::make_unique
--------------------------------------------------------------
Goal:
    Demonstrate exclusive ownership and safe resource management using RAII.

Key takeaways:
    - unique_ptr owns exactly one object
    - unique_ptr cannot be copied, only moved
    - std::make_unique is the preferred way to create it
    - resource is automatically released when the unique_ptr goes out of scope
*/

#include <iostream>
#include <memory>
#include <string>

class Logger {
   public:
    explicit Logger(std::string name) : m_Name(std::move(name)) {
        std::cout << "[Logger] constructed: " << m_Name << "\n";
    }

    ~Logger() {
        std::cout << "[Logger] destructed: " << m_Name << "\n";
    }

    void Log(const std::string& msg) const {
        std::cout << "[" << m_Name << "] " << msg << "\n";
    }

   private:
    std::string m_Name;
};

class Service {
   public:
    // Dependency injection with exclusive ownership:
    explicit Service(std::unique_ptr<Logger> logger) : m_Logger(std::move(logger)) {
    }

    void DoWork() const {
        m_Logger->Log("Doing work...");
    }

   private:
    std::unique_ptr<Logger> m_Logger;
};

int main() {
    // Create a unique_ptr using make_unique:
    auto logger = std::make_unique<Logger>("UniqueLogger");

    // logger cannot be copied:
    // auto copy = logger; // <-- compile error

    // Transfer ownership into Service (move):
    Service service(std::move(logger));

    // logger is now empty (nullptr) after move:
    if (!logger) {
        std::cout << "Ownership transferred: logger is now nullptr\n";
    }

    service.DoWork();

    // When main() ends, Service is destroyed -> Logger is destroyed automatically.
    return 0;
}
