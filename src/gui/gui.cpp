#include "gui.hpp"

#include "../keterrain.hpp"
#include <imgui.h>
#include <SFML/System.hpp>
#include <thread>

sf::Clock ktp::gui::chronometer {};
ktp::KeTerrain* ktp::gui::keterrain {nullptr};
bool ktp::gui::generating_texture {false};
bool ktp::gui::saving_image {false};

void ktp::gui::layout() {
  // ImGui::ShowDemoWindow();
  ImGui::SetNextWindowSize(ImVec2(510, 528), ImGuiCond_FirstUseEver);

  ImGui::Text("Settings");
  ImGui::BeginDisabled(generating_texture);
    // seed
    seed();
    ImGui::Separator();
    // size
    size();
    ImGui::Separator();
    // frequency
    frequency();
    // gain
    gain();
    // octaves
    octaves();
    ImGui::Separator();
    // generation button
    generateTexture();
    ImGui::SameLine();
    // randomize button
    randomize();
    ImGui::SameLine();
    // change view button
    changeView();
    ImGui::Separator();
    saveImage();
  ImGui::EndDisabled();

  ImGui::Separator();
  if (saving_image) {
    ImGui::Text("Saving image...");
    return;
  }
  if (generating_texture) {
    ImGui::Text("Generating texture...");
  }
}

void ktp::gui::changeView() {
  constexpr auto colorized_text {"View colorized"};
  constexpr auto noise_text {"View noise"};
  static std::string button_text {noise_text};
  if (ImGui::Button(button_text.c_str())) {
    keterrain->switchTexture() ? button_text = colorized_text : button_text = noise_text;
  }
}

void ktp::gui::frequency() {
  constexpr auto frequency_format {"%.5f"};
  if (ImGui::InputFloat("Frequency", &ktr_config.frequency, 0.0001f, 0.001f, frequency_format)) {
    keterrain->updateTexture();
  }
}

void ktp::gui::gain() {
  if (ImGui::InputFloat("Gain", &ktr_config.gain, 0.001f, 0.01f)) {
    keterrain->updateTexture();
  }
}

void ktp::gui::generateTexture() {
  if (ImGui::Button("Generate texture")) {
    generating_texture = true;
    std::thread process_thread { [&] {
      chronometer.restart();
      keterrain->updateTexture();
      const auto elapsed_time {chronometer.getElapsedTime().asMilliseconds()};
      printf("Texture generated in %.4fs.\n", (double)elapsed_time * 0.001);
      generating_texture = false;
    }};
    process_thread.detach();
  }
}

void ktp::gui::randomize() {
  if (ImGui::Button("Randomize")) {
    keterrain->randomizeConfig();
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
}

void ktp::gui::seed() {
  ImGui::InputInt("Seed", &ktr_config.seed);
}

void ktp::gui::size() {
  ImGui::InputInt2("Size (x,y)", &ktr_config.size.x);
}

void ktp::gui::octaves() {
  if (ImGui::InputInt("Octaves", &ktr_config.octaves, 1, 1)) {
    keterrain->updateTexture();
  }
}
