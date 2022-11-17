#include "noise.hpp"

#include <glm/gtc/noise.hpp>
#include <SFML/Graphics.hpp>

ktp::NoiseData ktp::noise::perlin(const Size2D& size, double frequency) {
  NoiseData noise_data {};
  noise_data.resize(static_cast<std::size_t>(size.x * size.y));

  for (auto row = 0; row < size.y; ++row) {
    for (auto col = 0; col < size.x; ++col) {
      const double nx {(double)col / (double)size.x}, ny {(double)row / (double)size.y};
      const auto sample {glm::dvec2(frequency * nx, frequency * ny)};
      // result between [-1, 1]
      noise_data[col + size.x * row] = glm::perlin(sample);
    }
  }
  return noise_data;
}
