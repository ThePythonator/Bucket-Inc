#include "Game.hpp"

Game::Game() : BaseGame() {

}

void Game::start() {
	stage = new IntroStage();
}

void Game::end() {

}

void Game::load_data() {
	// Set up graphics_objects vectors:
	graphics_objects.image_ptrs = std::vector<Framework::Image*>(GRAPHICS_OBJECTS::IMAGES::TOTAL_IMAGES);
	graphics_objects.spritesheet_ptrs = std::vector<Framework::Spritesheet*>(GRAPHICS_OBJECTS::SPRITESHEETS::TOTAL_SPRITESHEETS);

	std::string ASSETS_PATH = Framework::SDLUtils::find_assets_path(PATHS::IMAGES::LOCATION + PATHS::IMAGES::MAIN_SPRITESHEET, PATHS::DEPTH);
	std::string IMAGES_PATH = ASSETS_PATH + PATHS::IMAGES::LOCATION;

	// Load spritesheet image
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::MAIN_SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE);

	// Load font image
	// Note: we *need* to add SURFACE flags because Font uses the surface bit
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::FONT_SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE | Framework::Image::Flags::SDL_SURFACE);

	// Load background image
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::BACKGROUND] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::BACKGROUND, Framework::Image::Flags::SDL_TEXTURE);

	// Load popup image
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::POPUP] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::POPUP, Framework::Image::Flags::SDL_TEXTURE);

	// Load button image
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::BUTTON] = Framework::create_image(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::BUTTON, Framework::Image::Flags::SDL_TEXTURE);

	// Create spritesheet from spritesheet image
	graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET] = new Framework::Spritesheet(graphics_objects.graphics_ptr, graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET], SPRITE::SIZE, SPRITE::SCALE);

	// Create spritesheet from font image
	graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::FONT_SPRITESHEET] = new Framework::Spritesheet(graphics_objects.graphics_ptr, graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::FONT_SPRITESHEET], SPRITE::SIZE, SPRITE::SCALE);
}

void Game::clear_data() {
	// Clear spritesheets
	for (Framework::Spritesheet* spritesheet_ptr : graphics_objects.spritesheet_ptrs) {
		delete spritesheet_ptr;
	}
	graphics_objects.spritesheet_ptrs.clear();

	// Clear images
	for (Framework::Image* image_ptr : graphics_objects.image_ptrs) {
		image_ptr->free();
		delete image_ptr;
	}
	graphics_objects.image_ptrs.clear();
}