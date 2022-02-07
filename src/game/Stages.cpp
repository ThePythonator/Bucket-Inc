#include "Stages.hpp"

// IntroStage

bool IntroStage::update(float dt) {
	_intro_timer.update(dt);

	if (_intro_timer.running()) {
		if (_intro_timer.time() > TIMINGS::INTRO::CUMULATIVE::FADE_OUT) {
			// Switch to title
			finish(new TitleStage());
		}
	}
	else {
		_intro_timer.start();
	}

	return true;
}

void IntroStage::render() {
	graphics_objects->graphics_ptr->fill(COLOURS::BLACK);

	// Render icon
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(SPRITE::INDEX::SPLASH_ICON, WINDOW::SIZE_HALF / SPRITE::SPLASH_ICON_SCALE - SPRITE::SIZE_HALF, SPRITE::SPLASH_ICON_SCALE);

	if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::INITIAL_DELAY) {
		// Black
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK);
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::FADE_IN) {
		// Fade in
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0xFF, 0x00, (_intro_timer.time() - TIMINGS::INTRO::CUMULATIVE::INITIAL_DELAY) / TIMINGS::INTRO::DURATION::FADE_IN));
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::INTRO_DELAY) {
		// Show image
		// i.e. don't render over the top
	}
	else if (_intro_timer.time() < TIMINGS::INTRO::CUMULATIVE::FADE_OUT) {
		// Fade out
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK, Framework::Curves::linear(0x00, 0xFF, (_intro_timer.time() - TIMINGS::INTRO::CUMULATIVE::INTRO_DELAY) / TIMINGS::INTRO::DURATION::FADE_OUT));
	}
	else {
		// Black
		graphics_objects->graphics_ptr->fill(COLOURS::BLACK);
	}
}

// TitleStage

void TitleStage::start() {
	buttons = setup_menu_buttons(graphics_objects, STRINGS::TITLE::BUTTONS);

	// Start timer
	_transition_timer.start();
}

bool TitleStage::update(float dt) {
	_transition_timer.update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && _button_selected == BUTTONS::NONE && _transition_timer.time() > TIMINGS::MENU::DURATION::FADE) {
			_button_selected = button.get_id();
			_transition_timer.reset();
			_transition_timer.start();
		}
	}

	if (_button_selected != BUTTONS::NONE && _transition_timer.time() > TIMINGS::MENU::DURATION::FADE) {
		// Next stage!
		switch (_button_selected) {
		case BUTTONS::TITLE::PLAY:
			finish(new GameStage());
			break;

		case BUTTONS::TITLE::SETTINGS:
			finish(new SettingsStage());
			break;

		case BUTTONS::TITLE::QUIT:
			// Returning false causes program to exit
			return false;
			// (so we don't need the break)

		default:
			break;
		}
	}

	return true;
}

void TitleStage::render() {
	render_menu(graphics_objects, _transition_timer, buttons, _button_selected);
} 

// SettingsStage

void SettingsStage::start() {
	buttons = setup_menu_buttons(graphics_objects, STRINGS::SETTINGS::BUTTONS);

	// Start timer
	_transition_timer.start();
}

bool SettingsStage::update(float dt) {
	_transition_timer.update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && _button_selected == BUTTONS::NONE && _transition_timer.time() > TIMINGS::MENU::DURATION::FADE) {
			_button_selected = button.get_id();

			if (_button_selected == BUTTONS::SETTINGS::BACK) {
				_transition_timer.reset();
				_transition_timer.start();
			}
		}
	}

	if (_button_selected != BUTTONS::NONE && _transition_timer.time() > TIMINGS::MENU::DURATION::FADE) {
		// Next stage!
		switch (_button_selected) {
		case BUTTONS::SETTINGS::SOUND:
			// todo
			// Un-select button
			_button_selected = BUTTONS::NONE;
			break;

		case BUTTONS::SETTINGS::MUSIC:
			// todo
			// Un-select button
			_button_selected = BUTTONS::NONE;
			break;

		case BUTTONS::SETTINGS::BACK:
			finish(new TitleStage());
			break;

		default:
			break;
		}
	}

	return true;
}

void SettingsStage::render() {
	render_menu(graphics_objects, _transition_timer, buttons, _button_selected);
}

// GameStage

void GameStage::start() {
	// Hide cursor
	//input->get_mouse()->set_cursor(false);
	//SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	//SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO));
	//SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT));

	//buttons = setup_menu_buttons(graphics_objects, STRINGS::SETTINGS::BUTTONS);

	// Start timer
	_transition_timer.start();
}

void GameStage::end() {
	// Un-hide cursor
	input->get_mouse()->set_cursor(true);
}

bool GameStage::update(float dt) {
	_transition_timer.update(dt);

	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
		// User has paused
		// Pass this stage to PausedStage so that it still renders in the background
		finish(new PausedStage(this), false); // NOTE: WE NEED TRANSITIONS!
	}

	return true;
}

void GameStage::render() {
	render_background_scene(graphics_objects); //, cracked_pipes

	// Render bucket
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->rect(SPRITE::RECT::BUCKET_RECT, input->get_mouse()->position() / SPRITE::SCALE - SPRITE::RECT::BUCKET_RECT.size / 2);

	handle_fade(graphics_objects, _transition_timer, FadeState::IN); // todo : get correct fade state

	// when fading to paused menu:
	// handle_fade(graphics_objects, _transition_timer, FadeState::OUT, 0x00, 0x7F); // todo: get FadeState
}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

void PausedStage::start() {
	//buttons = setup_menu_buttons(graphics_objects, STRINGS::SETTINGS::BUTTONS);

	// Start timer
	_transition_timer.start();
}

bool PausedStage::update(float dt) {
	_transition_timer.update(dt);

	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
		// Exit pause
		finish(_background_stage);
		// TODO: animation
		// TODO: button to return
	}

	return true;
}

void PausedStage::render() {
	// Render background stage
	_background_stage->render();

	// Fade out background graphics slightly
	handle_fade(graphics_objects, _transition_timer, FadeState::IN, 0x00, 0x7F); // todo: get FadeState

	render_popup_and_buttons(graphics_objects, _transition_timer, buttons, FadeState::IN); // todo: work out fade state
}