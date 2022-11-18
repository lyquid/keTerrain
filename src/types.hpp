/**
 * @file types.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Types and forward declarations file.
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#if !defined(KETERRAIN_SRC_TYPES_HPP_)
#define KETERRAIN_SRC_TYPES_HPP_

#include <glm/vec2.hpp>
#include <memory>
#include <vector>

namespace sf {
  // SFML
  class Clock;
  class Color;
  class Event;
  class Image;
  class RenderWindow;
  class Sprite;
  class Texture;
  class VideoMode;
}

namespace ktp {

  class KeTerrain;

  using NoiseData      = std::vector<float>;
  using Pixels         = std::vector<sf::Color>;
  using RawTextureData = std::vector<unsigned char>;
  using TexturePtr     = std::unique_ptr<sf::Texture>;
  using Size2D         = glm::vec<2, int>;
  using Size2Du        = glm::vec<2, unsigned int>;

  struct KeTerrainConfig {
    float     frequency {0.02f};
    float     gain {-0.5f};
    NoiseData noise_data {};
    int       octaves {8};
    int       seed {42};
    Size2D    size {1000, 1000};
    Size2D    starting_point {0, 0};
  };
}

#endif // KETERRAIN_SRC_TYPES_HPP_
