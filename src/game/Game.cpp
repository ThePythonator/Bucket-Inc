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

	std::string ASSETS_PATH = Framework::SDLUtils::find_assets_path(PATHS::IMAGES::LOCATION + PATHS::IMAGES::SPRITESHEET, PATHS::DEPTH);
	std::string IMAGES_PATH = ASSETS_PATH + PATHS::IMAGES::LOCATION;

	// Create spritesheet image
	Framework::Image* spritesheet_image_ptr = new Framework::Image();
	spritesheet_image_ptr->load(graphics_objects.graphics_ptr, IMAGES_PATH + PATHS::IMAGES::SPRITESHEET, Framework::Image::Flags::SDL_TEXTURE);
	graphics_objects.image_ptrs[GRAPHICS_OBJECTS::IMAGES::MAIN_SPRITESHEET] = spritesheet_image_ptr;

	// Create spritesheet from spritesheet image
	graphics_objects.spritesheet_ptrs[GRAPHICS_OBJECTS::SPRITESHEETS::MAIN_SPRITESHEET] = new Framework::Spritesheet(graphics_objects.graphics_ptr, spritesheet_image_ptr, SPRITE::SIZE, SPRITE::SCALE);
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