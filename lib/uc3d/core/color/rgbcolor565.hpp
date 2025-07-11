/**
 * @file RGBColor.h
 * @brief Defines the RGBColor class for managing and manipulating 16-bit RGB565 color values.
 *
 * The RGBColor class represents RGB colors in 16-bit format (RGB565) and provides methods for color manipulation,
 * including scaling brightness, adding values, hue shifting, and interpolating between colors.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <cstdint>
#include "../math/mathematics.hpp"
#include "../math/quaternion.hpp"
#include "../math/vector3d.hpp"
#include "../platform/ustring.hpp"

/**
 * @class RGBColor
 * @brief Encodes / manipulates an RGB colour stored as 16-bit **RGB565**.
 *
 * A copy keeps both the packed 16-bit value (`color`) **and** the original 8-bit
 * channels so further maths stay loss-free until you repack.
 */
class RGBColor {
public:
    /** Encoded 16-bit RGB565 value (bits 15-0 = RRRRRGGGGGGBBBBB) */
    uint16_t color = 0;

    /**
     * @brief Default constructor initializes the color to black (0, 0, 0).
     */
    RGBColor() = default;

    /**
     * @brief Constructor to initialize RGBColor with specified R, G, and B values.
     * @param R Red component (0-255).
     * @param G Green component (0-255).
     * @param B Blue component (0-255).
     */
    RGBColor(uint8_t r, uint8_t g, uint8_t b) { SetColor(r, g, b); }

    /**
     * @brief Copy constructor.
     * @param rgbColor Reference to an existing RGBColor object.
     */
    RGBColor(const RGBColor& other) = default;

    /**
     * @brief Constructor to initialize RGBColor from a Vector3D.
     * @param color Vector3D representing RGB values.
     */
    explicit RGBColor(const Vector3D& v) { SetColor(v.X, v.Y, v.Z); }

    /**
     * @brief Sets the RGB values of the color.
     * @param R Red component (0-255).
     * @param G Green component (0-255).
     * @param B Blue component (0-255).
     */
    void SetColor(uint8_t rIn, uint8_t gIn, uint8_t bIn){
        r = rIn; g = gIn; b = bIn;
        Pack();
    }

    /**
     * @brief Scales the brightness of the color to a maximum value.
     * @param maxBrightness The maximum brightness value (0-255).
     * @return A new RGBColor with scaled brightness.
     */
    [[nodiscard]] RGBColor Scale(uint8_t maxBrightness) const{
        auto scale = [maxBrightness](uint8_t c) -> uint8_t {
            return uint8_t(uint16_t(c) * maxBrightness / 255);
        };
        return RGBColor(scale(r), scale(g), scale(b));
    }

    /**
     * @brief Adds a value to each RGB component of the color.
     * @param value The value to add (0-255).
     * @return A new RGBColor with modified values.
     */
    [[nodiscard]] RGBColor Add(uint8_t value) const{
        auto add = [value](uint8_t c) -> uint8_t {
            return Mathematics::Constrain<uint8_t>(c + value, 0, 255);
        };
        return RGBColor(add(r), add(g), add(b));
    }

    /**
     * @brief Shifts the hue of the color by a specified angle in degrees.
     * @param hueDeg The angle in degrees to shift the hue.
     * @return A new RGBColor with the hue shifted.
     */
    [[nodiscard]] RGBColor HueShift(float hueDeg) const{
        const float halfRad = hueDeg * Mathematics::MPI / 360.0f;
        const float hueRat  = 0.5f * sinf(halfRad);
        Quaternion q(cosf(halfRad), hueRat, hueRat, hueRat);

        Vector3D v = q.RotateVector(Vector3D(r, g, b))
                         .Constrain(0.0f, 255.0f);

        return RGBColor(uint8_t(v.X), uint8_t(v.Y), uint8_t(v.Z));
    }

    /**
     * @brief Interpolates between two colors based on a ratio.
     * @param a The starting color.
     * @param b The ending color.
     * @param ratio A value between 0 and 1 representing the interpolation factor.
     * @return The interpolated RGBColor.
     */
    static RGBColor InterpolateColors(RGBColor a, RGBColor b, float ratio){
        auto lerp = [ratio](uint8_t x, uint8_t y) -> uint8_t {
            return uint8_t(float(x) * (1.0f - ratio) + float(y) * ratio);
        };
        return RGBColor(lerp(a.r, b.r), lerp(a.g, b.g), lerp(a.b, b.b));
    }

    /**
     * @brief Converts the RGBColor to a string representation.
     * @return A string in the format "[R, G, B]".
     */
    [[nodiscard]] uc3d::UString ToString() const{
        return "[" + uc3d::UString(Mathematics::DoubleToCleanString(r)) + ", " + uc3d::UString(Mathematics::DoubleToCleanString(g)) + ", " + uc3d::UString(Mathematics::DoubleToCleanString(b)) + "]";
    }

    /* expose channels for fast access */
    uint8_t r = 0, g = 0, b = 0;

private:
    void Pack(){
        color = (uint16_t(r >> 3) << 11) |
                (uint16_t(g >> 2) << 5)  |
                (uint16_t(b >> 3));
    }
};
