#pragma once

#include <vector>

#include "GraphicsObjects.hpp"
#include "Curves.hpp"
#include "Timer.hpp"
#include "Button.hpp"

#include "Constants.hpp"

#include "CrackedPipe.hpp"

enum class FadeState {
	NONE,
	IN,
	OUT
};

void render_background_scene(Framework::GraphicsObjects* graphics_objects, std::vector<CrackedPipe> cracked_pipes = {});

void render_menu(Framework::GraphicsObjects* graphics_objects, Framework::Timer& transition_timer, std::vector<Framework::Button> buttons, uint8_t button_selected);

void handle_fade(Framework::GraphicsObjects* graphics_objects, Framework::Timer& transition_timer, FadeState state);

std::vector<Framework::Button> setup_menu_buttons(Framework::GraphicsObjects* graphics_objects, std::vector<std::string> names);