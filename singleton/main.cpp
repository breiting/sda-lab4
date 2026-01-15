/*
Pattern: Singleton (Gamma et al.)
---------------------------------
Intent:
    Ensure a class has only one instance and provide a global access point to
it.

Use case (example):
    A central configuration registry used across an application.

Notes:
    Singleton is controversial in modern C++ design because it introduces global
state, hidden dependencies, and makes unit testing harder. Prefer dependency
injection where possible. If you must use it, keep it minimal and side-effect
free.
*/

#include <iostream>
#include <mutex>
#include <string>

namespace patterns {

class Config {
   public:
    static Config &Instance() {
        // Meyers' Singleton: thread-safe since C++11
        static Config s_Instance;
        return s_Instance;
    }

    void SetValue(std::string key, std::string value) {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_Key = std::move(key);
        m_Value = std::move(value);
    }

    std::string GetValue() const {
        std::lock_guard<std::mutex> lock(m_Mutex);
        return m_Key + "=" + m_Value;
    }

   private:
    Config() = default;

    // prevent copy/move
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;

    mutable std::mutex m_Mutex;
    std::string m_Key{"mode"};
    std::string m_Value{"default"};
};

}  // namespace patterns

int main() {
    using patterns::Config;

    Config::Instance().SetValue("mode", "release");
    std::cout << "Config: " << Config::Instance().GetValue() << "\n";

    // Same instance:
    auto &cfg = Config::Instance();
    std::cout << "Config again: " << cfg.GetValue() << "\n";
}
