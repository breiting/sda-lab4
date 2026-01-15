/*
Pattern: Factory Method (Gamma et al.)
-------------------------------------
Intent:
    Define an interface for creating an object, but let subclasses decide which
    class to instantiate. Factory Method lets a class defer instantiation to
subclasses.

Use case (example):
    An importer framework where different creators return different parsers
based on the file type (JSON, XML, ...).
*/

#include <iostream>
#include <memory>
#include <string>

namespace patterns {

// Interface
class Document {
   public:
    virtual ~Document() = default;
    virtual std::string Render() const = 0;
};

class JsonDocument final : public Document {
   public:
    std::string Render() const override {
        return "Rendering JSON document";
    }
};

class XmlDocument final : public Document {
   public:
    std::string Render() const override {
        return "Rendering XML document";
    }
};

// Creator
class DocumentLoader {
   public:
    virtual ~DocumentLoader() = default;

    // Factory Method
    virtual std::unique_ptr<Document> Create() const = 0;

    void LoadAndRender() const {
        auto doc = Create();
        std::cout << doc->Render() << "\n";
    }
};

class JsonLoader final : public DocumentLoader {
   public:
    std::unique_ptr<Document> Create() const override {
        return std::make_unique<JsonDocument>();
    }
};

class XmlLoader final : public DocumentLoader {
   public:
    std::unique_ptr<Document> Create() const override {
        return std::make_unique<XmlDocument>();
    }
};

}  // namespace patterns

int main() {
    using namespace patterns;

    JsonLoader json;
    XmlLoader xml;

    json.LoadAndRender();
    xml.LoadAndRender();
}
