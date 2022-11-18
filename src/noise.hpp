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
 * @brief Generates Simplex noise data between [-1, 1].
 * @param config The config!
 */
void simplexFastNoise(KeTerrainConfig& config);

/**
 * @brief Generates Perlin noise data between [-1, 1].
 * @param config The config!
 */
void perlinGLM(KeTerrainConfig& config);

} } // namespace noise/ktp

#endif // KETERRAIN_SRC_NOISE_HPP_
