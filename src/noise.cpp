#include "noise.hpp"

#include <FastNoise/FastNoise.h>
#include <glm/gtc/noise.hpp>

ktp::NoiseData ktp::noise::perlinFastNoise(const Size2D& size, float frequency, int seed) {

  const auto simplex {FastNoise::New<FastNoise::OpenSimplex2>()};
  const auto fractal {FastNoise::New<FastNoise::FractalFBm>()};
  NoiseData noise_data(static_cast<std::size_t>(size.x * size.y));
  fractal->SetSource(simplex);
  fractal->SetOctaveCount(8);
  fractal->GenUniformGrid2D(noise_data.data(), 0.f, 0.f, size.x, size.y, frequency, seed);

  return noise_data;
}

ktp::NoiseData ktp::noise::perlinGLM(const Size2D& size, float frequency) {
  NoiseData noise_data {};
  noise_data.resize(static_cast<std::size_t>(size.x * size.y));

  for (auto row = 0; row < size.y; ++row) {
    for (auto col = 0; col < size.x; ++col) {
      const float nx {(float)col / (float)size.x}, ny {(float)row / (float)size.y};
      const auto sample {glm::vec2(frequency * nx, frequency * ny)};
      // result between [-1, 1]
      noise_data[col + size.x * row] = glm::perlin(sample);
    }
  }
  return noise_data;
}
