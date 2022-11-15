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
  void run();

 private:

  sf::Clock m_delta_clock {};
  sf::VideoMode m_desktop;
  sf::RenderWindow m_window;

};

} // namespace ktp

#endif // KETERRAIN_SRC_KETERRAIN_HPP_
