#pragma once

#include "BaseStage.hpp"

#include "Timer.hpp"
#include "Curves.hpp"

class IntroStage : public Framework::BaseStage {
public:
	IntroStage();

	void update(float dt, Framework::InputHandler& input);
	void render(Framework::Graphics& graphics);

private:
	Framework::Timer _intro_timer;
};

class TitleStage : public Framework::BaseStage {
public:
	TitleStage();

	void update(float dt, Framework::InputHandler& input);
	void render(Framework::Graphics& graphics);

private:
	Framework::Timer _transition_timer;

	int temp_x, temp_y;
	bool temp_b;
};

class SettingsStage : public Framework::BaseStage {
public:
	SettingsStage();

	void update(float dt, Framework::InputHandler& input);
	void render(Framework::Graphics& graphics);
};

class GameStage : public Framework::BaseStage {
public:
	GameStage();

	void update(float dt, Framework::InputHandler& input);
	void render(Framework::Graphics& graphics);
};

class PausedStage : public Framework::BaseStage {
public:
	PausedStage(BaseStage* background_stage);

	void update(float dt, Framework::InputHandler& input);
	void render(Framework::Graphics& graphics);

private:
	BaseStage* _background_stage;
};