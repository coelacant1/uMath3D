#include "../../../include/um3d/geometry/2d/ellipse.hpp"

Ellipse2D::Ellipse2D(Vector2D center, Vector2D size, float rotation) : Shape(center, size / 2.0f, rotation) {}

bool Ellipse2D::IsInShape(Vector2D point) const {
    float x = (point.X - center.X);
    float y = (point.Y - center.Y);

    float sinR = sinf(rotation * Mathematics::MPID180);
    float cosR = cosf(rotation * Mathematics::MPID180);

    float xP = x * cosR - y * sinR; // rotate about center
    float yP = y * cosR + x * sinR; // rotate about center

    float xQuot = xP * xP / (size.X * size.X); // size is twice radius
    float yQuot = yP * yP / (size.Y * size.Y);

    return xQuot + yQuot < 1.0f;
}
