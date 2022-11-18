#include "gui.hpp"

#include "../keterrain.hpp"
#include <imgui.h>
#include <SFML/System.hpp>
#include <thread>

sf::Clock ktp::gui::chronometer {};

void ktp::gui::layout(KeTerrain& keterrain) {
  // ImGui::ShowDemoWindow();

  static bool processing {false};

  ImGui::SetNextWindowSize(ImVec2(510, 528), ImGuiCond_FirstUseEver);

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("Close");
      ImGui::EndMenu();
    }
     ImGui::EndMenuBar();
  }

  ImGui::Text("Settings");
  ImGui::BeginDisabled(processing);
    // seed
    ImGui::InputInt("Seed", &ktr_config.seed);
    // size
    if (ImGui::InputInt("Width", &ktr_config.size.x, 1, 50)) {}
    if (ImGui::InputInt("Height", &ktr_config.size.y, 1, 50)) {}
    // frequency
    constexpr auto frequency_format {"%.5f"};
    if (ImGui::InputFloat("Frequency", &ktr_config.frequency, 0.0001f, 0.001f, frequency_format)) {
      keterrain.updateTexture();
    }
    // octaves
    if (ImGui::InputInt("Octaves", &ktr_config.octaves, 1, 1)) {
      keterrain.updateTexture();
    }
    ImGui::Separator();
    constexpr auto colorized_text {"View colorized"};
    constexpr auto noise_text {"View noise"};
    static std::string button_text {colorized_text};
    // button for generation
    if (ImGui::Button("Generate texture")) {
      processing = true;
      std::thread process_thread { [&] {
        chronometer.restart();
        keterrain.updateTexture();
        const auto elapsed_time {chronometer.getElapsedTime().asMilliseconds()};
        printf("elapsed time: %.4fs.\n", (double)elapsed_time / 1000.0);
        processing = false;
      }};
      process_thread.detach();
    }
    ImGui::SameLine();
    if (ImGui::Button("Randomize")) {
      keterrain.randomizeConfig();
    }
    ImGui::SameLine();
    if (ImGui::Button(button_text.c_str())) {
      if (keterrain.switchTexture()) {
        button_text = colorized_text;
      } else {
        button_text = noise_text;
      }
    }
  ImGui::EndDisabled();

  ImGui::Separator();
  if (processing) {
    ImGui::Text("Generating texture...");
  }
}
