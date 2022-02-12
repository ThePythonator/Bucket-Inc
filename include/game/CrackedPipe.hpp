#pragma once

#include <cstdint>

#include "Timer.hpp"
#include "Curves.hpp"

#include "Constants.hpp"

class CrackedPipe {
public:
	CrackedPipe();
	CrackedPipe(uint16_t sprite_index, uint8_t id, uint8_t drop_count);

	void update(float dt);

	uint8_t get_id();
	uint8_t get_sprite_index();

	bool can_create_drop();
	Framework::vec2 create_drop();
	bool finished();

	Framework::vec2 get_position();

private:
	uint8_t _id = 0;
	uint8_t _sprite_index = 0;

	uint8_t _drops_left = 0;

	float _delay = 0.0f;

	Framework::Timer _timer;
};