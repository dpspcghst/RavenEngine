// Circle.h
#include "Shape2D.h"

namespace RavenEngine {
    class Circle : public Shape2D {
    public:
        Circle();
        Circle(float radius, int segments);
        ~Circle();

        void Create() override;
        void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
        int GetVertexCount() const override;

    private:
        float radius;
        int segments;
        GLuint shaderProgram;
    };
}