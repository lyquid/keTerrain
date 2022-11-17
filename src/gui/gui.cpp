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
    // size
    static glm::vec<2, int> size {500, 500};
    if (ImGui::InputInt("Width", &size.x, 1, 50)) {}
    if (ImGui::InputInt("Height", &size.y, 1, 50)) {}
    // frequency
    static float frequency {10.f};
    constexpr auto frequency_format {"%.5f"};
    if (ImGui::InputFloat("Frequency", &frequency, 0.1f, 1.f, frequency_format)) {
      if (!first_use) keterrain.updateTexture(noise::perlin(size, frequency));
    }
    ImGui::Separator();
    // button for generation
    if (ImGui::Button("Generate texture")) {
      processing = true;
      std::thread process_thread { [&] {
        keterrain.resetTexture(size, noise::perlin(size, frequency));
        processing = false;
        first_use = false;
      }};
      process_thread.detach();
    }
    ImGui::Separator();
  ImGui::EndDisabled();

  ImGui::Separator();
  if (processing) {
    ImGui::Text("Generating texture...");
  }
}
