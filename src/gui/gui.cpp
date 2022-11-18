#include "gui.hpp"

#include "../keterrain.hpp"
#include "../noise.hpp"
#include <imgui.h>
#include <thread>

void ktp::gui::layout(KeTerrain& keterrain) {
  // ImGui::ShowDemoWindow();

  static bool first_use {true};
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
    static int seed {42};
    ImGui::InputInt("Seed", &seed);
    // size
    static glm::vec<2, int> size {1000, 1000};
    if (ImGui::InputInt("Width", &size.x, 1, 50)) {}
    if (ImGui::InputInt("Height", &size.y, 1, 50)) {}
    // frequency
    static float frequency {0.02f};
    constexpr auto frequency_format {"%.5f"};
    if (ImGui::InputFloat("Frequency", &frequency, 0.0001f, 0.001f, frequency_format)) {
      if (!first_use) keterrain.updateTexture(noise::perlinFastNoise(size, frequency, seed));
    }
    ImGui::Separator();
    constexpr auto colorized_text {"View colorized"};
    constexpr auto noise_text {"View noise"};
    static std::string button_text {colorized_text};
    // button for generation
    if (ImGui::Button("Generate texture")) {
      processing = true;
      std::thread process_thread { [&] {
        keterrain.resetTexture(size, noise::perlinFastNoise(size, frequency, seed));
        processing = false;
        first_use = false;
        button_text = colorized_text;
      }};
      process_thread.detach();
    }
    ImGui::SameLine();
    if (ImGui::Button(button_text.c_str()) && !first_use) {
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
