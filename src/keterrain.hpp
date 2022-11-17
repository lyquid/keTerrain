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
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ktp {

class KeTerrain {
 public:

  KeTerrain();
  ~KeTerrain() { ImGui::SFML::Shutdown(); }
  void run();
  void resetTexture(const Size2Du& size, const RawTextureData& new_data);
  auto windowSize() const { return m_window_size; }

 private:

  Size2Du m_window_size {1600, 1200};

  sf::Clock m_delta_clock {};
  sf::VideoMode m_desktop;
  sf::RenderWindow m_window;

  sf::Sprite m_sprite {};
  TexturePtr m_texture {nullptr};
};

} // namespace ktp

#endif // KETERRAIN_SRC_KETERRAIN_HPP_
