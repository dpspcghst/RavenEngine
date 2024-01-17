// Plane.h
#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

namespace RavenEngine {

class Plane : public Shape {
public:
    Plane();
    ~Plane();
    void Create() override;
};

} // namespace RavenEngine

#endif // PLANE_H