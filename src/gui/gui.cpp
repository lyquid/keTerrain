#include "gui.hpp"

#include "../keterrain.hpp"
#include <imgui.h>
#include <SFML/System.hpp>
#include <thread>

sf::Clock ktp::gui::chronometer {};
ktp::KeTerrain* ktp::gui::keterrain {nullptr};
bool ktp::gui::generating_texture {false};
bool ktp::gui::saving_image {false};
bool ktp::gui::size_changed {false};
bool ktp::gui::frequency_locked {false};
bool ktp::gui::seed_locked {false};

void ktp::gui::layout() {
  // ImGui::ShowDemoWindow();

  ImGui::SetNextWindowSize(ImVec2(510, 528), ImGuiCond_FirstUseEver);
  if (!ImGui::Begin("KeTerrain configuration")) {
    ImGui::End();
    return;
  }
  ImGui::Text("Texture settings");
  ImGui::BeginDisabled(generating_texture);
    size();
    changeView();
    ImGui::SameLine();
    invertElevation();
    ImGui::SameLine();
    saveImage();
    ImGui::SameLine();
    defaults();
  ImGui::EndDisabled();
  ImGui::Separator();
  ImGui::Text("Generation settings");
  ImGui::BeginDisabled(generating_texture);
    tileable();
    seed();
    frequency();
    gain();
    lacunarity();
    octaves();
    ImGui::Separator();
    // generation button
    generateTexture();
    ImGui::SameLine();
    // randomize button
    randomize();
    ImGui::SameLine();
  ImGui::EndDisabled();
  ImGui::Separator();
  if (saving_image) {
    ImGui::Text("Saving image...");
    return;
  }
  if (generating_texture) {
    ImGui::Text("Generating texture...");
  }
  ImGui::End();
}

void ktp::gui::changeView() {
  constexpr auto colorized_text {"View colorized"};
  constexpr auto noise_text {"View noise"};
  static std::string button_text {noise_text};
  if (ImGui::Button(button_text.c_str())) {
    keterrain->switchTexture() ? button_text = colorized_text : button_text = noise_text;
  }
}

void ktp::gui::defaults() {
  if (ImGui::Button("Default")) {
    ktr_config = KeTerrainConfig{};
    ktr_config.noise_data.resize(static_cast<std::size_t>(ktr_config.size.x * ktr_config.size.y));
    keterrain->generateNoise();
    keterrain->updateTexture();
  }
}

void ktp::gui::frequency() {
  constexpr auto frequency_format {"%.5f"};
  ImGui::BeginDisabled(frequency_locked);
    if (ImGui::InputFloat("Frequency", &ktr_config.frequency, 0.0001f, 0.001f, frequency_format)) {
      keterrain->generateNoise();
      keterrain->updateTexture();
      size_changed = false;
    }
  ImGui::EndDisabled();
  ImGui::SameLine();
  ImGui::Checkbox("Locked##frequency", &frequency_locked);
}

void ktp::gui::gain() {
  if (ImGui::InputFloat("Gain", &ktr_config.gain, 0.001f, 0.01f)) {
    keterrain->generateNoise();
    keterrain->updateTexture();
    size_changed = false;
  }
}

void ktp::gui::generateTexture() {
  if (ImGui::Button("Generate texture")) {
    generating_texture = true;
    std::thread process_thread { [&] {
      chronometer.restart();
      keterrain->generateNoise();
      keterrain->updateTexture();
      const auto elapsed_time {chronometer.getElapsedTime().asMilliseconds()};
      printf("Texture generated in %.4fs.\n", (double)elapsed_time * 0.001);
      generating_texture = false;
      size_changed = false;
    }};
    process_thread.detach();
  }
}

void ktp::gui::invertElevation() {
  if (ImGui::Button("Invert elevation")) {
    keterrain->invertElevation();
    keterrain->updateTexture();
    size_changed = false;
  }
}

void ktp::gui::lacunarity() {
  if (ImGui::InputFloat("Lacunarity", &ktr_config.lacunarity, 0.001f, 0.01f)) {
    keterrain->generateNoise();
    keterrain->updateTexture();
    size_changed = false;
  }
}

void ktp::gui::randomize() {
  if (ImGui::Button("Randomize")) {
    keterrain->randomizeConfig(!frequency_locked, !seed_locked);
  }
}

void ktp::gui::saveImage() {
  if (ImGui::Button("Save image")) {
    saving_image = true;
    generating_texture = true;
    std::thread process_thread { [&] {
      chronometer.restart();
      keterrain->saveImage();
      const auto elapsed_time {chronometer.getElapsedTime().asMilliseconds()};
      printf("Image saved in %.4fs.\n", (double)elapsed_time * 0.001);
      saving_image = false;
      generating_texture = false;
    }};
    process_thread.detach();
  }
  if (size_changed) {
    ImGui::SameLine();
    ImGui::Text("Generate a new texture to apply size changes!");
  }
}

void ktp::gui::seed() {
  ImGui::BeginDisabled(seed_locked);
    if(ImGui::InputInt("Seed", &ktr_config.seed)) {
      keterrain->generateNoise();
      keterrain->updateTexture();
      size_changed = false;
    }
  ImGui::EndDisabled();
  ImGui::SameLine();
  ImGui::Checkbox("Locked##seed", &seed_locked);
}

void ktp::gui::size() {
  if (ImGui::InputInt2("Size (x,y)", &ktr_config.size.x)) {
    size_changed = true;
  }
}

void ktp::gui::tileable() {
  if (ImGui::Checkbox("Tileable", &ktr_config.tileable)) {
    keterrain->generateNoise();
    keterrain->updateTexture();
    size_changed = false;
  }
}

void ktp::gui::octaves() {
  if (ImGui::InputInt("Octaves", &ktr_config.octaves, 1, 1)) {
    keterrain->generateNoise();
    keterrain->updateTexture();
    size_changed = false;
  }
}
