#pragma once

#include <cstdint>

class CrackedPipe {
public:
	CrackedPipe();
	CrackedPipe(uint16_t sprite_index, uint8_t _id);

	uint8_t get_id();
	uint8_t get_sprite_index();

private:
	uint8_t _id = 0;
	uint8_t _sprite_index = 0;
};