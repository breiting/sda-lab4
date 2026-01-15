/*
Pattern: Adapter (Gamma et al.)
-------------------------------
Intent:
    Convert the interface of a class into another interface clients expect.
    Adapter lets classes work together that couldn't otherwise due to
incompatible interfaces.

Use case (example):
    Integrate a legacy logger into a new ILogger interface expected by modern
code.
*/

#include <iostream>
#include <memory>
#include <string>

namespace patterns {

// Target interface (what the new code expects)
class ILogger {
   public:
    virtual ~ILogger() = default;
    virtual void LogInfo(const std::string &msg) = 0;
};

// Adaptee (legacy / incompatible)
class LegacyLogger {
   public:
    void Write(const char *message) {
        std::cout << "[Legacy] " << message << "\n";
    }
};

// Adapter
class LegacyLoggerAdapter final : public ILogger {
   public:
    explicit LegacyLoggerAdapter(std::shared_ptr<LegacyLogger> legacy) : m_Legacy(std::move(legacy)) {
    }

    void LogInfo(const std::string &msg) override {
        m_Legacy->Write(msg.c_str());
    }

   private:
    std::shared_ptr<LegacyLogger> m_Legacy;
};

static void BusinessLogic(ILogger &logger) {
    logger.LogInfo("Starting simulation step...");
    logger.LogInfo("Finished simulation step.");
}

}  // namespace patterns

int main() {
    using namespace patterns;

    auto legacy = std::make_shared<LegacyLogger>();
    LegacyLoggerAdapter adapter(legacy);

    BusinessLogic(adapter);
}
