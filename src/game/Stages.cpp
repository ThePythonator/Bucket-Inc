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

	// Load highscore
	highscore = load_save_data(graphics_objects->asset_path);

	// Set title text
	_title_text = Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], STRINGS::TITLE::TITLE, COLOURS::GREY, SPRITE::TITLE_FONT_SCALE);

	// Start transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	transition->open();
}

bool TitleStage::update(float dt) {
	transition->update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			_button_selected = button.get_id();
			transition->close();
		}
	}

	if (transition->is_closed()) {
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
	_title_text.set_text(STRINGS::TITLE::TITLE + std::to_string(highscore));
	render_menu_with_text(graphics_objects, transition->percent(), buttons, _button_selected, _title_text);

	transition->render(graphics_objects->graphics_ptr);
} 

// SettingsStage

void SettingsStage::start() {
	buttons = setup_menu_buttons(graphics_objects, STRINGS::SETTINGS::BUTTONS);

	// Set title text
	_title_text = Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], STRINGS::SETTINGS::TITLE, COLOURS::GREY, SPRITE::TITLE_FONT_SCALE);

	// Start transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	transition->open();
}

bool SettingsStage::update(float dt) {
	transition->update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			_button_selected = button.get_id();

			if (_button_selected == BUTTONS::SETTINGS::BACK) {
				transition->close();
			}
		}
	}

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
		if (transition->is_closed()) {
			// Go back!
			finish(new TitleStage());
		}
		break;

	default:
		break;
	}

	return true;
}

void SettingsStage::render() {
	render_menu_with_text(graphics_objects, transition->percent(), buttons, _button_selected, _title_text);

	transition->render(graphics_objects->graphics_ptr);
}

// GameStage

GameStage::GameStage() {
	cracked_pipe_gen_time = GAME::INITIAL_CRACKED_PIPE_DELAY;
	cracked_pipe_drop_count = GAME::INITIAL_CRACKED_PIPE_DROP_COUNT;

	cracked_pipe_gen_timer.start();

	// Create first cracked pipe
	create_cracked_pipe(cracked_pipes, cracked_pipe_drop_count);

	// Setup
	water_level = 0;
	score = 0;
	paused = false;
}

void GameStage::start() {
	// Hide cursor
	input->get_mouse()->set_cursor(false);
	//SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
	//SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO));
	//SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT));

	//buttons = setup_menu_buttons(graphics_objects, STRINGS::SETTINGS::BUTTONS);

	// Start transition (keep transition as pause_transition if level was paused)
	if (!paused) {
		set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	}
	transition->open();

	paused = false;
}

void GameStage::end() {
	// Un-hide cursor
	input->get_mouse()->set_cursor(true);
}

bool GameStage::update(float dt) {
	transition->update(dt);

	cracked_pipe_gen_timer.update(dt);

	// Set bucket pos
	bucket_pos = input->get_mouse()->position() - GAME::BUCKET_SIZE / 2;

	create_cracked_pipe(cracked_pipes, cracked_pipe_gen_timer, cracked_pipe_gen_time, cracked_pipe_drop_count);

	for (CrackedPipe& pipe : cracked_pipes) {
		pipe.update(dt);

		if (pipe.can_create_drop()) {
			drops.push_back(pipe.create_drop());
		}
	}

	cracked_pipes.erase(std::remove_if(cracked_pipes.begin(), cracked_pipes.end(), [](CrackedPipe& pipe) { return pipe.finished(); }), cracked_pipes.end());

	// All a mess!
	for (Framework::vec2& drop_pos : drops) {
		drop_pos.y += GAME::DROP_FALL_RATE * dt;

		if (drop_pos.y >= WINDOW::HEIGHT / 2) {
			water_level++;
		}
		else if (Framework::colliding(Framework::Rect((drop_pos + GAME::DROP_COLLIDER_OFFSET) * SPRITE::SCALE, GAME::DROP_COLLIDER * SPRITE::SCALE), Framework::Rect(bucket_pos + GAME::BUCKET_COLLIDER_OFFSET, GAME::BUCKET_COLLIDER_SIZE))) {
			// We caught the drop of water
			score++;
			drop_pos.y = WINDOW::HEIGHT; // set it to be completely off the screen so that it gets removed (but don't deal damage because of it)
		}
	}

	drops.erase(std::remove_if(drops.begin(), drops.end(), [](Framework::vec2& pos) { return pos.y >= WINDOW::HEIGHT / SPRITE::SCALE; }), drops.end());

	if (transition->is_open()) {
		if (water_level > GAME::MAX_WATER_HEIGHT) {
			// End game
			//set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
			set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::PAUSE_TRANSITION]); // maybe use pause transition?
			transition->close();
		}

		if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
			// User has paused
			// Pass this stage to PausedStage so that it still renders in the background
			paused = true;

			// We need to change transition so it only fades to semi-transparent
			set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::PAUSE_TRANSITION]);
			transition->close();
		}
	}

	if (transition->is_closed()) {
		if (paused) {
			// Paused game
			finish(new PausedStage(this), false);
		}
		else {
			// Must be end of game
			finish(new EndStage(score));
		}
	}

	return true;
}

void GameStage::render() {
	render_background_scene(graphics_objects, cracked_pipes);

	// Render drops
	for (Framework::vec2 drop_pos : drops) {
		//graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->rect(SPRITE::RECT::BUCKET_RECT, input->get_mouse()->position() / SPRITE::BUCKET_SCALE - SPRITE::RECT::BUCKET_RECT.size / 2, SPRITE::BUCKET_SCALE);

		// to fix
		drop_pos *= 2;
		drop_pos += SPRITE::SIZE_HALF;
		graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(24, drop_pos, SPRITE::BUCKET_SCALE);
		graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(32, drop_pos + Framework::Vec(0, SPRITE::SIZE), SPRITE::BUCKET_SCALE);
	}

	// Render bucket
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->rect(SPRITE::RECT::BUCKET_RECT, bucket_pos, SPRITE::BUCKET_SCALE);

	// Render score
	graphics_objects->spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET]->sprite(SPRITE::INDEX::SCORE_BOX, Framework::Vec(WINDOW::WIDTH / SPRITE::UI_SCALE - SPRITE::SIZE, 0), SPRITE::UI_SCALE);
	graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT]->render_text(std::to_string(score), Framework::Vec(WINDOW::WIDTH - SPRITE::SIZE_HALF, 0), COLOURS::BLACK, Framework::Font::TOP_RIGHT);

	transition->render(graphics_objects->graphics_ptr);
}

// PausedStage

PausedStage::PausedStage(BaseStage* background_stage) : BaseStage() {
	// Save the background stage so we can still render it, and then go back to it when done
	_background_stage = background_stage;
}

void PausedStage::start() {
	buttons = setup_menu_buttons(graphics_objects, STRINGS::PAUSED::BUTTONS);

	// Set title text
	_title_text = Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], STRINGS::PAUSED::TITLE, COLOURS::GREY, SPRITE::TITLE_FONT_SCALE);

	// Start transition (but we don't actually render the fade-in)
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	transition->open();
}

bool PausedStage::update(float dt) {
	transition->update(dt);

	if (input->just_down(Framework::KeyHandler::Key::ESCAPE) || input->just_down(Framework::KeyHandler::Key::P)) {
		transition->close();
	}

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			_button_selected = button.get_id();
			transition->close();
		}
	}

	if (transition->is_closed()) {
		if (_button_selected == BUTTONS::PAUSED::EXIT) {
			delete _background_stage;
			finish(new TitleStage());
		}
		else {
			// Return to game (exit pause)
			finish(_background_stage);
		}
	}

	return true;
}

void PausedStage::render() {
	// Render background stage
	_background_stage->render();

	render_popup_and_buttons_with_text(graphics_objects, transition->percent(), buttons, transition->state() == Framework::BaseTransition::TransitionState::CLOSING || transition->is_closed() ? FadeState::OUT : FadeState::IN, _title_text);

	// Only show transition if exiting
	if (transition->state() == Framework::BaseTransition::TransitionState::CLOSING && _button_selected == BUTTONS::PAUSED::EXIT) transition->render(graphics_objects->graphics_ptr);
}

// EndStage

EndStage::EndStage(uint16_t _score) {
	score = _score;
}

void EndStage::start() {
	buttons = setup_menu_buttons(graphics_objects, STRINGS::END::BUTTONS);

	// Set title text
	_title_text = Framework::Text(graphics_objects->font_ptrs[GRAPHICS_OBJECTS::FONTS::MAIN_FONT], STRINGS::END::TITLE, COLOURS::GREY, SPRITE::TITLE_FONT_SCALE);

	// Start transition
	set_transition(graphics_objects->transition_ptrs[GRAPHICS_OBJECTS::TRANSITIONS::FADE_TRANSITION]);
	transition->open();

	// Write score if greater than current highscore
	if (score > load_save_data(graphics_objects->asset_path)) {
		write_save_data(graphics_objects->asset_path, score);
	}
}

bool EndStage::update(float dt) {
	transition->update(dt);

	// Update buttons
	for (Framework::Button& button : buttons) {
		button.update(input);

		if (button.pressed() && transition->is_open()) {
			_button_selected = button.get_id();
			transition->close();
		}
	}

	if (transition->is_closed()) {
		switch (_button_selected) {
		case BUTTONS::END::RETRY:
			// Retry
			finish(new GameStage());
			break;

		case BUTTONS::END::EXIT:
			// Go back!
			finish(new TitleStage());
			break;

		default:
			break;
		}
	}

	return true;
}

void EndStage::render() {
	// todo: render score
	
	_title_text.set_text(STRINGS::END::TITLE + std::to_string(score));
	render_menu_with_text(graphics_objects, transition->percent(), buttons, _button_selected, _title_text);

	transition->render(graphics_objects->graphics_ptr);
}