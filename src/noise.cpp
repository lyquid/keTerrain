#include "noise.hpp"

#include <FastNoise/FastNoise.h>
#include <glm/gtc/noise.hpp>

void ktp::noise::simplexFastNoise(KeTerrainConfig& config) {

  const auto simplex {FastNoise::New<FastNoise::Simplex>()};
  const auto fractal {FastNoise::New<FastNoise::FractalFBm>()};

  fractal->SetSource(simplex);
  fractal->SetOctaveCount(config.octaves);
  fractal->SetGain(config.gain);
  fractal->SetLacunarity(config.lacunarity);
  fractal->GenUniformGrid2D(
    config.noise_data.data(),
    config.starting_point.x, config.starting_point.y,
    config.size.x, config.size.y,
    config.frequency,
    config.seed
  );
}

void ktp::noise::perlinGLM(KeTerrainConfig& config) {

  for (auto row = 0; row < config.size.y; ++row) {
    for (auto col = 0; col < config.size.x; ++col) {
      const float nx {(float)col / (float)config.size.x}, ny {(float)row / (float)config.size.y};
      const auto sample {glm::vec2(config.frequency * nx, config.frequency * ny)};
      // result between [-1, 1]
      config.noise_data[col + config.size.x * row] = glm::perlin(sample);
    }
  }
}
