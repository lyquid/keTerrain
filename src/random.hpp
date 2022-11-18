/**
 * @file random.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Random number generation utilities.
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#if !defined(KETERRAIN_SRC_RANDOM_HPP_)
#define KETERRAIN_SRC_RANDOM_HPP_

#include "types.hpp"

namespace ktp { namespace rng {

sf::Color randomColor(int min = 0, int max = 255);

double randomDouble(double min = 0.0, double max = 1.0);

float randomFloat(float min = 0.f, float max = 1.f);

int randomInt(int min, int max);

} } // namespace rng / ktp

#endif // KETERRAIN_SRC_RANDOM_HPP_
