/*
Pattern: Proxy (Gamma et al.)
-----------------------------
Intent:
    Provide a surrogate or placeholder to control access to another object.

Use case (example):
    Lazy-loading a large image: load only when needed, cache afterward.
*/

#include <iostream>
#include <memory>
#include <string>

namespace patterns {

class IImage {
   public:
    virtual ~IImage() = default;
    virtual void Draw() = 0;
};

class RealImage final : public IImage {
   public:
    explicit RealImage(std::string filename) : m_Filename(std::move(filename)) {
        // Simulate expensive load
        std::cout << "Loading image from disk: " << m_Filename << "\n";
    }

    void Draw() override {
        std::cout << "Drawing image: " << m_Filename << "\n";
    }

   private:
    std::string m_Filename;
};

class ImageProxy final : public IImage {
   public:
    explicit ImageProxy(std::string filename) : m_Filename(std::move(filename)) {
    }

    void Draw() override {
        if (!m_Real) {
            m_Real = std::make_unique<RealImage>(m_Filename);  // lazy init
        }
        m_Real->Draw();
    }

   private:
    std::string m_Filename;
    std::unique_ptr<RealImage> m_Real;
};

}  // namespace patterns

int main() {
    using namespace patterns;

    ImageProxy img("huge_texture.png");
    std::cout << "Proxy created. No load yet.\n";

    std::cout << "First draw:\n";
    img.Draw();

    std::cout << "Second draw:\n";
    img.Draw();
}
