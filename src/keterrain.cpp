#include "keterrain.hpp"
#include <imgui.h>

ktp::KeTerrain::KeTerrain():
  m_desktop(sf::VideoMode::getDesktopMode()),
  m_window(sf::VideoMode(1600, 1200, m_desktop.bitsPerPixel), "keTerrain")
{
  ImGui::SFML::Init(m_window);
}

void ktp::KeTerrain::run() {
  while (m_window.isOpen()) {
    sf::Event event {};
    while (m_window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(m_window, event);
      if (event.type == sf::Event::Closed) m_window.close();
    }
    ImGui::SFML::Update(m_window, m_delta_clock.restart());

    ImGui::ShowDemoWindow();
    // ktp::gui::layout();

    m_window.clear();
    ImGui::SFML::Render(m_window);
    m_window.display();
  }
  ImGui::SFML::Shutdown();
}
