/*
Pattern: Facade (Gamma et al.)
------------------------------
Intent:
    Provide a unified, simplified interface to a set of interfaces in a
subsystem. Facade defines a higher-level interface that makes the subsystem
easier to use.

Use case (example):
    Hide complexity of a "render pipeline" behind a single RenderFrame() call.
*/

#include <iostream>
#include <string>

namespace patterns {

// Subsystem classes (complex internals)
class ShaderCompiler {
   public:
    void Compile(const std::string &shaderName) {
        std::cout << "Compiling shader: " << shaderName << "\n";
    }
};

class MeshUploader {
   public:
    void Upload(const std::string &meshName) {
        std::cout << "Uploading mesh: " << meshName << "\n";
    }
};

class Renderer {
   public:
    void Draw(const std::string &meshName) {
        std::cout << "Drawing mesh: " << meshName << "\n";
    }
};

// Facade
class RenderFacade {
   public:
    RenderFacade() = default;

    void RenderFrame(const std::string &shader, const std::string &mesh) {
        m_Compiler.Compile(shader);
        m_Uploader.Upload(mesh);
        m_Renderer.Draw(mesh);
    }

   private:
    ShaderCompiler m_Compiler;
    MeshUploader m_Uploader;
    Renderer m_Renderer;
};

}  // namespace patterns

int main() {
    using namespace patterns;

    RenderFacade engine;
    engine.RenderFrame("basic_shader", "3d_mesh");
}
