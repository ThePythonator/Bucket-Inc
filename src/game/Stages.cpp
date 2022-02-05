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

void TitleStage::end() {

}

bool TitleStage::update(float dt) {
	_transition_timer.update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && _button_selected == BUTTONS::NONE) {
			_button_selected = button.get_id();
			_transition_timer.reset();
			_transition_timer.start();

			if (_button_selected == BUTTONS::TITLE::QUIT) {
				// Returning false causes program to exit
				return false;
			}
		}
	}

	if (_button_selected != BUTTONS::NONE && _transition_timer.time() > TIMINGS::MENU::DURATION::FADE_OUT) {
		// Next stage!
		switch (_button_selected) {
		case BUTTONS::TITLE::PLAY:
			finish(new GameStage());
			break;

		case BUTTONS::TITLE::SETTINGS:
			finish(new SettingsStage());
			break;

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

void SettingsStage::end() {

}

bool SettingsStage::update(float dt) {
	_transition_timer.update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && _button_selected == BUTTONS::NONE) {
			_button_selected = button.get_id();

			if (_button_selected == BUTTONS::SETTINGS::BACK) {
				_transition_timer.reset();
				_transition_timer.start();
			}
		}
	}

	if (_button_selected != BUTTONS::NONE && _transition_timer.time() > TIMINGS::MENU::DURATION::FADE_OUT) {
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

GameStage::GameStage() : BaseStage() {

}

bool GameStage::update(float dt) {
	// Note: if pausing game, call
	// finish(new PausedStage(this), false);

	return true;
}

void GameStage::render() {

}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

bool PausedStage::update(float dt) {
	if (false) {
		// Exit pause
		finish(_background_stage);
	}

	return true;
}

void PausedStage::render() {
	// Render background stage
	_background_stage->render();
}