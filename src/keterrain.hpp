/**
 * @file keterrain.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#if !defined(KETERRAIN_SRC_KETERRAIN_HPP_)
#define KETERRAIN_SRC_KETERRAIN_HPP_

#include "types.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ktp {

extern KeTerrainConfig ktr_config;

class KeTerrain {
 public:

  KeTerrain();
  ~KeTerrain();

  static RawTextureData noiseToColorData(const NoiseData& noise);
  static RawTextureData noiseToTextureData(const NoiseData& noise);

  void randomizeConfig();
  void run();
  void saveImage() const;
  bool switchTexture() {
    m_noise_sprite ? m_sprite.setTexture(*m_colored_texture) : m_sprite.setTexture(*m_noise_texture);
    m_noise_sprite = !m_noise_sprite;
    return m_noise_sprite;
  }
  void updateTexture();
  auto windowSize() const { return m_window_size; }

 private:

  static void flattenColor(RawTextureData& texture_data, const sf::Color& color) {
    texture_data.push_back(color.r);
    texture_data.push_back(color.g);
    texture_data.push_back(color.b);
    texture_data.push_back(color.a);
  }

  static void flattenNoise(RawTextureData& texture_data, double value) {
    flattenColor(texture_data, {
      // convert to [0, 255] before pushing
      static_cast<sf::Uint8>(value * 255.0),
      static_cast<sf::Uint8>(value * 255.0),
      static_cast<sf::Uint8>(value * 255.0),
      255u
    });
  }

  Size2Du m_window_size {1920, 1080};

  sf::Clock m_delta_clock {};
  sf::VideoMode m_desktop;
  sf::RenderWindow m_window;

  sf::Sprite m_sprite {};
  bool m_noise_sprite {false};
  TexturePtr m_colored_texture {nullptr};
  TexturePtr m_noise_texture {nullptr};
};

} // namespace ktp

#endif // KETERRAIN_SRC_KETERRAIN_HPP_
