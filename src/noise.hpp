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

RawTextureData perlin(const Size2D& size, float scale = 1.f);

} } // namespace noise/ktp

#endif // KETERRAIN_SRC_NOISE_HPP_
