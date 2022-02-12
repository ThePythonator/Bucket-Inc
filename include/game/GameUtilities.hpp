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

void render_popup_and_buttons(Framework::GraphicsObjects* graphics_objects, float transition_percent, std::vector<Framework::Button>& buttons, FadeState state);

void render_menu(Framework::GraphicsObjects* graphics_objects, float transition_percent, std::vector<Framework::Button>& buttons, uint8_t button_selected);
void render_menu_with_fade(Framework::GraphicsObjects* graphics_objects, Framework::Timer& transition_timer, std::vector<Framework::Button>& buttons, uint8_t button_selected);

void handle_fade(Framework::GraphicsObjects* graphics_objects, float transition_percent, FadeState state, uint8_t low = 0x00, uint8_t high = 0xFF);

std::vector<Framework::Button> setup_menu_buttons(Framework::GraphicsObjects* graphics_objects, const std::vector<std::string>& names);

void create_cracked_pipe(std::vector<CrackedPipe>& cracked_pipes, Framework::Timer& cracked_pipe_gen_timer, float& cracked_pipe_gen_time, float& cracked_pipe_drop_count);