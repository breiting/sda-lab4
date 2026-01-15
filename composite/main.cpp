/*
Pattern: Composite (Gamma et al.)
---------------------------------
Intent:
    Compose objects into tree structures to represent part-whole hierarchies.
    Composite lets clients treat individual objects and compositions uniformly.

Use case (example):
    A simple file system: File and Directory both implement Node.
*/

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace patterns {

class Node {
   public:
    virtual ~Node() = default;
    virtual std::string Name() const = 0;
    virtual std::size_t Size() const = 0;
    virtual void Print(int indent) const = 0;
};

class File final : public Node {
   public:
    File(std::string name, std::size_t size) : m_Name(std::move(name)), m_Size(size) {
    }

    std::string Name() const override {
        return m_Name;
    }
    std::size_t Size() const override {
        return m_Size;
    }

    void Print(int indent) const override {
        std::cout << std::string(static_cast<std::size_t>(indent), ' ') << "- " << m_Name << " (" << m_Size
                  << " bytes)\n";
    }

   private:
    std::string m_Name;
    std::size_t m_Size;
};

class Directory final : public Node {
   public:
    explicit Directory(std::string name) : m_Name(std::move(name)) {
    }

    void Add(std::unique_ptr<Node> child) {
        m_Children.push_back(std::move(child));
    }

    std::string Name() const override {
        return m_Name;
    }

    std::size_t Size() const override {
        std::size_t total = 0;
        for (const auto &c : m_Children) {
            total += c->Size();
        }
        return total;
    }

    void Print(int indent) const override {
        std::cout << std::string(static_cast<std::size_t>(indent), ' ') << "+ " << m_Name << " (" << Size()
                  << " bytes)\n";
        for (const auto &c : m_Children) {
            c->Print(indent + 2);
        }
    }

   private:
    std::string m_Name;
    std::vector<std::unique_ptr<Node>> m_Children;
};

}  // namespace patterns

int main() {
    using namespace patterns;

    auto root = std::make_unique<Directory>("root");
    root->Add(std::make_unique<File>("README.md", 1200));

    auto src = std::make_unique<Directory>("src");
    src->Add(std::make_unique<File>("main.cpp", 3400));
    src->Add(std::make_unique<File>("util.cpp", 800));

    root->Add(std::move(src));

    root->Print(0);
    std::cout << "Total size: " << root->Size() << " bytes\n";
}
