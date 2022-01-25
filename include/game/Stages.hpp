#pragma once

#include "BaseStage.hpp"

class TitleStage : public Framework::BaseStage {
public:
	TitleStage();

	void update(float dt, Framework::InputHandler& input);
	void render(Framework::Graphics& graphics);

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