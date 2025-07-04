/**
 * @file ImageSequence.h
 * @brief Declares the ImageSequence class for managing and rendering image sequences.
 *
 * This file defines the ImageSequence class, which extends the Material class to
 * support animations by cycling through a sequence of images at a specified frame rate.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include <stdint.h>
#include "../../core/math/mathematics.hpp" // Include for math operations.
#include "image.hpp" // Include for handling individual images.
#include "../../core/platform/time.hpp"

/**
 * @class ImageSequence
 * @brief Manages and renders a sequence of images as an animation.
 *
 * The ImageSequence class allows rendering animations by cycling through a series of
 * images at a specified frame rate. It provides controls for position, size, rotation,
 * and color manipulation of the animation.
 */
class ImageSequence {
private:
    Image* image; ///< Pointer to the Image object used for rendering.
    const uint8_t** data; ///< Pointer to an array of image data.
    unsigned long startTime = 0; ///< Timestamp of when the sequence started.
    unsigned int imageCount = 0; ///< Total number of images in the sequence.
    float fps = 24.0f; ///< Frames per second for the animation.
    float frameTime = 0.0f; ///< Time interval between frames.
    unsigned int currentFrame = 0; ///< Current frame index in the sequence.

protected:
    /**
     * @brief Constructs an ImageSequence object.
     *
     * @param image Pointer to the base Image object.
     * @param data Pointer to the image data array.
     * @param imageCount Total number of images in the sequence.
     * @param fps Frame rate of the animation.
     */
    ImageSequence(Image* image, const uint8_t** data, unsigned int imageCount, float fps);

public:
    Image* GetImage();

    /**
     * @brief Sets the frames per second (FPS) for the animation.
     *
     * @param fps The desired frame rate.
     */
    void SetFPS(float fps);

    /**
     * @brief Sets the size of the image sequence.
     *
     * @param size A Vector2D object specifying the width and height.
     */
    void SetSize(Vector2D size);

    /**
     * @brief Sets the position offset of the image sequence.
     *
     * @param offset A Vector2D object specifying the position offset.
     */
    void SetPosition(Vector2D offset);

    /**
     * @brief Sets the rotation angle of the image sequence.
     *
     * @param angle The rotation angle in degrees.
     */
    void SetRotation(float angle);

    /**
     * @brief Resets the image sequence to its initial state.
     */
    void Reset();

    /**
     * @brief Updates the current frame based on elapsed time.
     */
    void Update();

    /**
     * @brief Gets the color at an xy coordinate
     *
     * @param point the point in space to retrieve the color
     */
    RGBColor GetColorAtCoordinate(Vector2D point);
};
