#include "keterrain.hpp"

#include "noise.hpp"
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

void ktp::KeTerrain::resetTexture(const Size2Du& size, const RawTextureData& new_data) {
  // new texture
  m_texture = std::make_unique<sf::Texture>();
  m_texture->create(size.x, size.y);
  m_texture->update(new_data.data());
  // point the sprite to the new texture
  m_sprite.setTexture(*m_texture, true);
}
