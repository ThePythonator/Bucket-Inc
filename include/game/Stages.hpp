#pragma once

#include <algorithm>

#include "BaseStage.hpp"

#include "Timer.hpp"
#include "Curves.hpp"

#include "FadeTransition.hpp"

#include "GameUtilities.hpp"

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
	uint8_t _button_selected = BUTTONS::NONE;
};

class SettingsStage : public Framework::BaseStage {
public:
	void start();

	bool update(float dt);
	void render();

private:
	Framework::Timer _transition_timer;

	uint8_t _button_selected = BUTTONS::NONE;
};

class GameStage : public Framework::BaseStage {
public:
	GameStage();

	void start();
	void end();

	bool update(float dt);
	void render();

private:
	Framework::Timer _transition_timer;
	Framework::Timer cracked_pipe_gen_timer;
	float cracked_pipe_gen_time;
	float cracked_pipe_drop_count;

	std::vector<CrackedPipe> cracked_pipes;
	std::vector<Framework::vec2> drops;
};

class PausedStage : public Framework::BaseStage {
public:
	PausedStage(BaseStage* background_stage);

	void start();

	bool update(float dt);
	void render();

private:
	Framework::Timer _transition_timer;

	BaseStage* _background_stage;
};