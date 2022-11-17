#include "keterrain.hpp"

#include "noise.hpp"
#include "palette.hpp"
#include "gui/gui.hpp"
#include <imgui-SFML.h>

ktp::KeTerrain::KeTerrain():
  m_desktop(sf::VideoMode::getDesktopMode()),
  m_window(sf::VideoMode(m_window_size.x, m_window_size.y, m_desktop.bitsPerPixel), "keTerrain") {

  if (!ImGui::SFML::Init(m_window)) {
    printf("ERROR initializing imgui-sfml");
  }
}

ktp::KeTerrain::~KeTerrain() { ImGui::SFML::Shutdown(); }


ktp::RawTextureData ktp::KeTerrain::noiseToColorData(const NoiseData& noise) {
  RawTextureData texture_data {};
  texture_data.reserve(noise.size() * 4);
  for (auto value: noise) {
    if (value < -0.4) {
      flattenColor(texture_data, Palette::dark_blue);
    }
    else if (value < 0.0) {
      flattenColor(texture_data, Palette::blue);
    }
    else if (value < 0.05) {
      flattenColor(texture_data, Palette::yellow);
    }
    else if (value < 0.2) {
      flattenColor(texture_data, Palette::green);
    }
    else if (value < 0.8) {
      flattenColor(texture_data, Palette::dark_green);
    }
    else if (value < 0.9) {
      flattenColor(texture_data, Palette::grey);
    }
    else {
      flattenColor(texture_data, Palette::white);
    }
  }
  return texture_data;
}

ktp::RawTextureData ktp::KeTerrain::noiseToTextureData(const NoiseData& noise) {
  RawTextureData texture_data {};
  texture_data.reserve(noise.size() * 4);
  for (auto value: noise) {
    // value to [0, 1] range
    value = value / 2.0 + 0.5;
    // transform and push to the texture data
    flattenNoise(texture_data, value);
  }
  return texture_data;
}

void ktp::KeTerrain::run() {
  while (m_window.isOpen()) {
    sf::Event event {};
    while (m_window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(m_window, event);
      if (event.type == sf::Event::Closed) m_window.close();
    }
    ImGui::SFML::Update(m_window, m_delta_clock.restart());

    m_window.clear();

    m_window.draw(m_sprite);

    gui::layout(*this);
    ImGui::SFML::Render(m_window);

    m_window.display();
  }
}

void ktp::KeTerrain::resetTexture(const Size2Du& size, const NoiseData& new_data) {
  // new noise texture
  m_noise_texture = std::make_unique<sf::Texture>();
  m_noise_texture->create(size.x, size.y);
  m_noise_texture->update(noiseToTextureData(new_data).data());
  // point the sprite to the new noise texture
  m_sprite.setTexture(*m_noise_texture, true);
  // new colorized texture
  m_colored_texture = std::make_unique<sf::Texture>();
  m_colored_texture->create(size.x, size.y);
  m_colored_texture->update(noiseToColorData(new_data).data());
}
