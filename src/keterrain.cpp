#include "keterrain.hpp"

#include "noise.hpp"
#include "palette.hpp"
#include "random.hpp"
#include "gui/gui.hpp"
#include <imgui-SFML.h>

ktp::KeTerrainConfig ktp::ktr_config {};

ktp::KeTerrain::KeTerrain():
  m_desktop(sf::VideoMode::getDesktopMode()),
  m_window(sf::VideoMode(m_window_size.x, m_window_size.y, m_desktop.bitsPerPixel), "keTerrain") {

  if (!ImGui::SFML::Init(m_window)) {
    printf("ERROR initializing imgui-sfml");
  }

  ktr_config.frequency = rng::randomFloat(0.0005f, 0.02f);
  ktr_config.seed = rng::randomInt(1, 400);
  // ktr_config.octaves = rng::randomInt(1, 8);
  updateTexture();
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
    else if (value < 0.3) {
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

void ktp::KeTerrain::updateTexture() {
  static Size2D previous_size {};
  // see if we have to resize the textures and sprite
  if (previous_size == ktr_config.size) {
    // process the noise
    noise::simplexFastNoise(ktr_config);
    // update textures
    m_noise_texture->update(noiseToTextureData(ktr_config.noise_data).data());
    m_colored_texture->update(noiseToColorData(ktr_config.noise_data).data());
  } else {
    // resize the noise data's vector
    ktr_config.noise_data.resize(static_cast<std::size_t>(ktr_config.size.x * ktr_config.size.y));
    // process the noise
    noise::simplexFastNoise(ktr_config);
    // new noise texture
    m_noise_texture = std::make_unique<sf::Texture>();
    m_noise_texture->create(ktr_config.size.x, ktr_config.size.y);
    m_noise_texture->update(noiseToTextureData(ktr_config.noise_data).data());
    // new colorized texture
    m_colored_texture = std::make_unique<sf::Texture>();
    m_colored_texture->create(ktr_config.size.x, ktr_config.size.y);
    m_colored_texture->update(noiseToColorData(ktr_config.noise_data).data());
    // point the sprite to the new texture
    if (m_noise_sprite) {
      m_sprite.setTexture(*m_noise_texture, true);
    } else {
      m_sprite.setTexture(*m_colored_texture, true);
    }
  }
  // save the previous (current) size
  previous_size = ktr_config.size;
}
