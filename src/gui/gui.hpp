/**
 * @file gui.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief GUI for the app.
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#if !defined(KETERRAIN_SRC_GUI_GUI_HPP_)
#define KETERRAIN_SRC_GUI_GUI_HPP_

#include "../types.hpp"

namespace ktp { namespace gui {

extern sf::Clock chronometer;
extern KeTerrain* keterrain;
extern bool generating_texture;
extern bool saving_image;
extern bool size_changed;
extern bool frequency_locked;
extern bool seed_locked;

void layout();

void changeView();
void defaults();
void frequency();
void gain();
void generateTexture();
void invertElevation();
void lacunarity();
void randomize();
void saveImage();
void seed();
void size();
void tileable();
void octaves();

} } // namespace gui/ktp

#endif // KETERRAIN_SRC_GUI_GUI_HPP_
