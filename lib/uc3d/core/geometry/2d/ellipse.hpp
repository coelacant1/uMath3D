/**
 * @file Ellipse.h
 * @brief Defines the Ellipse class for representing elliptical shapes in 2D space.
 *
 * The Ellipse class provides functionality to define an ellipse by its center, size, and rotation,
 * and check if a given point lies within the ellipse's boundaries.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "shape.hpp"

/**
 * @class Ellipse
 * @brief Represents an ellipse in 2D space.
 */
class Ellipse2D : public Shape {
public:
    /**
     * @brief Constructs an Ellipse object with specified center, size, and rotation.
     * @param center Center point of the ellipse.
     * @param size Dimensions of the ellipse (width and height).
     * @param rotation Rotation angle of the ellipse in degrees.
     */
    Ellipse2D(Vector2D center, Vector2D size, float rotation = 0.0f);

    /**
     * @brief Constructs an Ellipse object with specified center, size, and rotation.
     * @param bounds Ellipse bounds.
     * @param rotation Rotation angle of the ellipse in degrees.
     */
    Ellipse2D(Bounds bounds, float rotation = 0.0f);

    /**
     * @brief Checks if a given point lies within the ellipse's boundaries.
     * @param point The point to check.
     * @return True if the point is within the ellipse, otherwise false.
     */
    bool IsInShape(Vector2D point) override;
};
