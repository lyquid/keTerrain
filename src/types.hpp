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

#include <glm/vec2.hpp>
#include <memory>
#include <vector>

namespace sf {
  // SFML
  class Clock;
  class Color;
  class Event;
  class RenderWindow;
  class Sprite;
  class Texture;
  class VideoMode;
}

namespace ktp {

  class KeTerrain;

  using Pixels         = std::vector<sf::Color>;
  using RawTextureData = std::vector<unsigned char>;
  using TexturePtr     = std::unique_ptr<sf::Texture>;
  using Size2D         = glm::vec<2, int>;
  using Size2Du        = glm::vec<2, unsigned int>;
}
