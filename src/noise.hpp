/**
 * @file noise.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Noise generators.
 * @version 0.1
 * @date 2022-11-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#if !defined(KETERRAIN_SRC_NOISE_HPP_)
#define KETERRAIN_SRC_NOISE_HPP_

#include "types.hpp"

namespace ktp { namespace noise {

/**
 * @brief Generates Perlin noise data between [-1, 1].
 * @param size The size desired.
 * @param frequency The frequency.
 * @return A vector with the noise data.
 */
NoiseData perlinFastNoise(const Size2D& size, float frequency = 0.02f, int seed = 42);

/**
 * @brief Generates Perlin noise data between [-1, 1].
 * @param size The size desired.
 * @param frequency The frequency.
 * @return A vector with the noise data.
 */
NoiseData perlinGLM(const Size2D& size, float frequency = 10.f);

} } // namespace noise/ktp

#endif // KETERRAIN_SRC_NOISE_HPP_
