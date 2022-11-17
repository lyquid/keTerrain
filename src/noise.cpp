#include "noise.hpp"

#include <glm/gtc/noise.hpp>
#include <SFML/Graphics.hpp>

ktp::RawTextureData ktp::noise::perlin(const Size2D& size, double scale) {
  RawTextureData texture_data {};
  texture_data.reserve(static_cast<std::size_t>(size.x * size.y * 4));

  for (auto row = 0; row < size.y; ++row) {
    for (auto col = 0; col < size.x; ++col) {
      const auto sample {glm::dvec2(col, row)};
      // res between [-1, 1]
      auto res {glm::perlin(sample * scale)};
      // res to [0, 1] range
      res = res / 2.0 + 0.5;
      // multiply the sample by white
      const auto color {glm::dvec3(1.0, 1.0, 1.0) * res};
      // convert to [0, 255] before pushing
      texture_data.push_back(static_cast<sf::Uint8>(color.r * 255.0));
      texture_data.push_back(static_cast<sf::Uint8>(color.g * 255.0));
      texture_data.push_back(static_cast<sf::Uint8>(color.b * 255.0));
      texture_data.push_back(255u);
    }
  }
  return texture_data;
}
