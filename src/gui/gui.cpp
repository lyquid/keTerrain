#include "gui.hpp"

#include "../keterrain.hpp"
#include "../noise.hpp"
#include <imgui.h>
#include <thread>

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

    static float scale {0.01f};
    static glm::vec<2, int> size {500, 500};
    if (ImGui::InputInt("Width", &size.x, 1, 50)) {}
    if (ImGui::InputInt("Height", &size.y, 1, 50)) {}
    constexpr auto scale_format {"%.5f"};
    if (ImGui::InputFloat("Scale", &scale, 0.001f, 0.1f, scale_format)) {}

    ImGui::Separator();

    if (ImGui::Button("Generate texture")) {
      processing = true;
      std::thread process_thread { [&] {
        keterrain.resetTexture(size, noise::perlin(size, scale));
        processing = false;
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
