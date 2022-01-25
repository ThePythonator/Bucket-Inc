#include "Spritesheet.hpp"

namespace Framework {

	Spritesheet::Spritesheet() {

	}

	Spritesheet::Spritesheet(Graphics* graphics, Image* spritesheet_image, uint8_t sprite_size, uint8_t default_scale) {
		_graphics = graphics;
		_spritesheet_image = spritesheet_image;

		_sprite_size = sprite_size;
		_default_scale = default_scale;

		// Get width and height of spritesheet
		SDL_QueryTexture(spritesheet_texture, NULL, NULL, &_w, &_h);

		_rows = _h / _sprite_size;
		_columns = _w / _sprite_size;
	}

	void Spritesheet::sprite(uint16_t index, float x, float y, SpriteTransform transform) {
		sprite(index, x, y, _default_scale, transform);
	}

	void Spritesheet::sprite(uint16_t index, float x, float y, float scale, SpriteTransform transform) {
		// TODO: handle transforms
		Rect src = Rect(_sprite_size * (index % columns), _sprite_size * (index / columns), _sprite_size, _sprite_size);
		Rect dst = Rect(x * scale, y * scale, _sprite_size * scale, _sprite_size * scale);
		_spritesheet_image->render(_graphics, src, dst);
	}


	void Spritesheet::sprite(uint16_t index, float x, float y, float scale, float angle, vec2 centre, SpriteTransform transform) {
		// TODO: handle transforms
		// TODO: handle rotations
		Rect src = Rect(_sprite_size * (index % columns), _sprite_size * (index / columns), _sprite_size, _sprite_size);
		Rect dst = Rect(x * scale, y * scale, _sprite_size * scale, _sprite_size * scale);
		_spritesheet_image->render(_graphics, src, dst);
	}

	//void Spritesheet::sprite(uint16_t index, float x, float y, float scale) {
	//	// Render sprite at index from texture to screen
	//	SDL_Rect src_rect{ sprite_size * (index % columns), sprite_size * (index / columns), sprite_size, sprite_size };
	//	SDL_Rect dst_rect{ static_cast<int>(x * scale), static_cast<int>(y * scale), static_cast<int>(sprite_size * scale), static_cast<int>(sprite_size * scale) };

	//	SDL_RenderCopy(renderer, spritesheet_texture, &src_rect, &dst_rect);
	//}

	//void Spritesheet::sprite(uint16_t index, float x, float y, float scale, SDL_RendererFlip flip) {
	//	sprite(index, x, y, scale, 0.0f, NULL, flip);
	//}

	//void Spritesheet::sprite(uint16_t index, float x, float y, float scale, float angle, SDL_Point* center, SDL_RendererFlip flip) {
	//	// Render sprite at index from texture to screen
	//	SDL_Rect src_rect{ sprite_size * (index % columns), sprite_size * (index / columns), sprite_size, sprite_size };
	//	SDL_Rect dst_rect{ static_cast<int>(x * scale), static_cast<int>(y * scale), static_cast<int>(sprite_size * scale), static_cast<int>(sprite_size * scale) };

	//	// Note: possible issue here, if center != NULL, the value at that address is altered, i.e. it's modified globally, not just locally
	//	if (center != NULL) {
	//		center->x *= scale;
	//		center->y *= scale;
	//	}

	//	SDL_RenderCopyEx(renderer, spritesheet_texture, &src_rect, &dst_rect, angle, center, flip);
	//}

	//void Spritesheet::sprite_scaled(uint16_t index, float x, float y) {
	//	// Render sprite at index from texture to screen
	//	sprite(index, x, y, scale);
	//}

	//void Spritesheet::sprite_scaled(uint16_t index, float x, float y, SDL_RendererFlip flip) {
	//	sprite_scaled(index, x, y, 0.0f, NULL, flip);
	//}

	//void Spritesheet::sprite_scaled(uint16_t index, float x, float y, float angle, SDL_Point* center, SDL_RendererFlip flip) {
	//	// Render sprite at index from texture to screen
	//	sprite(index, x, y, scale, angle, center, flip);
	//}

	//void Spritesheet::rect(SDL_Rect* src_rect, float x, float y) {
	//	SDL_Rect dst_rect{ static_cast<int>(x), static_cast<int>(y), src_rect->w, src_rect->h };

	//	SDL_RenderCopy(renderer, spritesheet_texture, src_rect, &dst_rect);
	//}

	//void Spritesheet::rect(SDL_Rect* src_rect, float x, float y, float scale) {
	//	SDL_Rect dst_rect{ static_cast<int>(x * scale), static_cast<int>(y * scale), static_cast<int>(src_rect->w * scale), static_cast<int>(src_rect->h * scale) };

	//	SDL_RenderCopy(renderer, spritesheet_texture, src_rect, &dst_rect);
	//}

	//void Spritesheet::rect_scaled(SDL_Rect* src_rect, float x, float y) {
	//	rect(src_rect, x, y, scale);
	//}


	//void Spritesheet::set_blend_mode(SDL_BlendMode blending)
	//{
	//	// Set blending type
	//	SDL_SetTextureBlendMode(spritesheet_texture, blending);
	//}

	//void Spritesheet::set_alpha(uint8_t alpha)
	//{
	//	// Set texture alpha
	//	SDL_SetTextureAlphaMod(spritesheet_texture, alpha);
	//}


	/*float Spritesheet::get_scale() {
		return scale;
	}*/

	/*uint8_t Spritesheet::get_alpha() {
		uint8_t alpha;
		SDL_GetTextureAlphaMod(spritesheet_texture, &alpha);
		return alpha;
	}*/

	/*SDL_Texture* Spritesheet::get_texture() {
		return spritesheet_texture;
	}*/

	//uint8_t Spritesheet::get_sprite_size() {
	//	return sprite_size;
	//}

}