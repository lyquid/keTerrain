#include "random.hpp"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

sf::Color ktp::rng::randomColor(int min, int max) {
  return sf::Color(randomInt(min, max), randomInt(min, max), randomInt(min, max));
}

double ktp::rng::randomDouble(double min, double max) {
  static std::uniform_real_distribution<double> dist(min, max);
  static std::mt19937 generator (std::chrono::steady_clock::now().time_since_epoch().count());
  return dist(generator);
}

float ktp::rng::randomFloat(float min, float max) {
  static std::uniform_real_distribution<float> dist(min, max);
  static std::mt19937 generator (std::chrono::steady_clock::now().time_since_epoch().count());
  return dist(generator);
}

int ktp::rng::randomInt(int min, int max) {
  static std::uniform_int_distribution<int> dist(min, max);
  static std::mt19937 generator (std::chrono::steady_clock::now().time_since_epoch().count());
  return dist(generator);
}
