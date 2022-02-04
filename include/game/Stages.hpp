#pragma once

#include <algorithm>

#include "BaseStage.hpp"

#include "Timer.hpp"
#include "Curves.hpp"

class IntroStage : public Framework::BaseStage {
public:
	bool update(float dt);
	void render();

private:
	Framework::Timer _intro_timer;
};

class TitleStage : public Framework::BaseStage {
public:
	void start();
	void end();

	bool update(float dt);
	void render();

private:
	Framework::Timer _transition_timer;
	
	std::vector<Framework::Text*> text_ptrs;
	std::vector<Framework::vec2> button_positions;

	uint8_t _button_selected = BUTTONS::NONE;
};

class SettingsStage : public Framework::BaseStage {
public:
	SettingsStage();

	bool update(float dt);
	void render();
};

class GameStage : public Framework::BaseStage {
public:
	GameStage();

	bool update(float dt);
	void render();
};

class PausedStage : public Framework::BaseStage {
public:
	PausedStage(BaseStage* background_stage);

	bool update(float dt);
	void render();

private:
	BaseStage* _background_stage;
};