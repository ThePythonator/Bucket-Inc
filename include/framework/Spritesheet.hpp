#pragma once

#include "Image.hpp"
#include "Transform.hpp"

namespace Framework {
	class Spritesheet {
	public:
		Spritesheet();
		Spritesheet(Graphics* graphics, Image* spritesheet_image, uint8_t sprite_size = 16, uint8_t default_scale = 1, bool scale_positions = true);

		void sprite(uint16_t index, vec2 position, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, float x, float y, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, vec2 position, float scale, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, float x, float y, float scale, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, vec2 position, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE);

		void rect(Rect src, vec2 position, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect src, float x, float y, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect src, vec2 position, float scale, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect src, float x, float y, float scale, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect src, vec2 position, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect src, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE);

		uint8_t get_sprite_size();
		uint8_t get_scale();

		Image* get_image();

		//void set_blend_mode(SDL_BlendMode blending);
		//void set_alpha(uint8_t alpha);

		//uint8_t get_alpha();

	private:
		Graphics* _graphics = nullptr; // Note that now it appears we don't even need this
		Image* _spritesheet_image = nullptr;

		uint32_t _w = 0;
		uint32_t _h = 0;
		uint8_t _rows = 0;
		uint8_t _columns = 0;

		uint8_t _sprite_size = 16;
		uint8_t _default_scale = 1;

		bool _scale_positions = false;
	};
}