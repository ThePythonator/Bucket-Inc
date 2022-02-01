#pragma once

#include "Image.hpp"
#include "Transform.hpp"

namespace Framework {
	class Spritesheet {
	public:
		Spritesheet();
		Spritesheet(Graphics* graphics, Image* spritesheet_image, uint8_t sprite_size = 16, uint8_t default_scale = 1);

		void sprite(uint16_t index, float x, float y, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, float x, float y, float scale, SpriteTransform transform = SpriteTransform::NONE);
		void sprite(uint16_t index, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE);

		void rect(Rect rect, float x, float y, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect rect, float x, float y, float scale, SpriteTransform transform = SpriteTransform::NONE);
		void rect(Rect rect, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform = SpriteTransform::NONE);

		uint8_t get_sprite_size();
		uint8_t get_scale();

		Image* get_image();

		//void sprite_scaled(uint16_t index, float x, float y);
		//void sprite_scaled(uint16_t index, float x, float y, SDL_RendererFlip flip);
		//void sprite_scaled(uint16_t index, float x, float y, float angle, SDL_Point* center, SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE);

		//void rect(SDL_Rect* src_rect, float x, float y);
		//void rect(SDL_Rect* src_rect, float x, float y, uint8_t scale);

		//void rect_scaled(SDL_Rect* src_rect, float x, float y);


		//void set_blend_mode(SDL_BlendMode blending);
		//void set_alpha(uint8_t alpha);


		//float get_scale();
		//uint8_t get_alpha();

	private:
		Graphics* _graphics = nullptr;
		Image* _spritesheet_image = nullptr;

		uint32_t _w = 0;
		uint32_t _h = 0;
		uint8_t _rows = 0;
		uint8_t _columns = 0;

		uint8_t _sprite_size = 16;
		uint8_t _default_scale = 1;
	};
}