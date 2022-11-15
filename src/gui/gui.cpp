#include "gui.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void ktp::gui::layout(){

}

void ktp::gui::start() {
  sf::VideoMode desktop {sf::VideoMode::getDesktopMode()};
  sf::RenderWindow window {sf::VideoMode(1024, 768, desktop.bitsPerPixel), "keTerrain"};
  if (!ImGui::SFML::Init(window)) return;

  sf::Clock delta_clock {};
  while (window.isOpen()) {
    sf::Event event {};
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);
      if (event.type == sf::Event::Closed) window.close();
    }
    ImGui::SFML::Update(window, delta_clock.restart());

    // ImGui::ShowDemoWindow();
    layout();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}
