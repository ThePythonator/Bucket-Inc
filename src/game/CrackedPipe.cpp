#include "CrackedPipe.hpp"

CrackedPipe::CrackedPipe() {

}
CrackedPipe::CrackedPipe(uint16_t sprite_index, uint8_t id, uint8_t drop_count) {
	_sprite_index = sprite_index;
	_id = id;
	_drops_left = drop_count;

	_timer.start();
	_delay = Framework::Curves::linear(GAME::CRACKED_PIPE_DROP_DELAY_MIN, GAME::CRACKED_PIPE_DROP_DELAY_MAX, Framework::randf());
}

void CrackedPipe::update(float dt) {
	_timer.update(dt);
}

uint8_t CrackedPipe::get_id() {
	return _id;
}
uint8_t CrackedPipe::get_sprite_index() {
	return _sprite_index;
}

bool CrackedPipe::can_create_drop() {
	return _timer.time() >= _delay && !finished();
}

Framework::vec2 CrackedPipe::create_drop() {
	_drops_left--;
	_timer.reset();
	_delay = Framework::Curves::linear(GAME::CRACKED_PIPE_DROP_DELAY_MIN, GAME::CRACKED_PIPE_DROP_DELAY_MAX, Framework::randf());

	return get_position();
}

bool CrackedPipe::finished() {
	return _drops_left == 0;
}

Framework::vec2 CrackedPipe::get_position() {
	return Framework::Vec(
		(_id % SPRITE::PIPES_ARRAY_WIDTH) * SPRITE::SIZE,
		(_id / SPRITE::PIPES_ARRAY_WIDTH) * SPRITE::SIZE
	);
}